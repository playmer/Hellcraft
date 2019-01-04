#pragma once

/*
State machine to manage game states and transitions.
Part of the game engine.
*/

// Standard Headers.
#include <stack>
#include <variant>
#include <utility>

namespace Engine {
    template <typename ...T>
    class GSM {
    public:
        using State = std::variant<T...>;
       
        void init();
        void cleanup();

        void changeState(State p_state);
        void pushState(State p_state);
        void popState();

        void handleEvents();
        void update();
        void draw();
        
    private:
        std::stack<std::variant<T...>> m_states; 
        bool m_running;
    };

    // Initalize the state manager. 
    template <typename ...T>
    void GSM<T...>::init() {
        m_running = true;
    }

    // Cleanup all states currently on the stack.
    // Mark machine as not running anymore.
    template <typename ...T>
    void GSM<T...>::cleanup() {
        // While there is still a state left, clean up resources and pop it.
        while(!m_states.empty()) {
            std::visit(
                [](auto& state){ state.cleanup(); },
                m_states.top()
            );
            m_states.pop();
        }
        m_running = false;
    }

    // Transition to a new state without preserving old one.
    template <typename ...T>
    void GSM<T...>::changeState(State p_state) {
        // Cleanup current state.
        if(!m_states.empty()) {
            std::visit(
                [](auto& state){ state.cleanup(); },
                m_states.top()
            );
            m_states.pop();
        }
        // Store and start up new state.
        m_states.push(std::move(p_state));
        std::visit(
            [](auto& state){ state.init(); },
            m_states.top()
        );
    }

    // Pause current state and switch to a new one.
    template <typename ...T>
    void GSM<T...>::pushState(State p_state) {
        // Pause current state.
        if(!m_states.empty()) {
            std::visit(
                [](auto& state){ state.pause(); },
                m_states.top()
            );
        }
        // Switch to new one and start it up.
        m_states.push(std::move(p_state));
        std::visit(
            [](auto& state){ state.init(); },
            m_states.top()
        );
    }

    // Cleanup current state and go back to previous state, resuming it.
    template <typename ...T>
    void GSM<T...>::popState() {
        // Cleanup current state.
        if(!m_states.empty()) {
            std::visit(
                [](auto& state){ state.cleanup(); },
                m_states.top()
            );
            m_states.pop();
        }
        // Resume previous state.
        if(!m_states.empty()) {
            std::visit(
                [](auto& state){ state.resume(); },
                m_states.top()
            );
        }
    }

    // Let the state handle events.
    template <typename ...T>
    void GSM<T...>::handleEvents() {
        std::visit(
            [](auto& state){ state.handleEvents(); },
            m_states.top()
        );
    }

    // Let the state update info, actors, etc.
    template <typename ...T>
    void GSM<T...>::update() {
        std::visit(
            [](auto& state){ state.update(); },
            m_states.top()
        );
    }

    // Let the state draw.
    template <typename ...T>
    void GSM<T...>::draw() {
        std::visit(
            [](auto& state){ state.draw(); },
            m_states.top()
        );
    }
}