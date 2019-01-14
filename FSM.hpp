#pragma once

/*
State machine to manage game states and transitions.
Part of the game engine.
*/

// Project Headers.
#include "Log.hpp"
#include "Window.hpp"
#include "Clock.hpp"
#include "Event.hpp"
// Standard Headers.
#include <stack>
#include <variant>
#include <utility>

namespace Engine {
    template <typename ...T>
    class FSM {
    public:
        using State = std::variant<T...>;
       
        void init();
        void cleanup();

        void changeState(State p_state);
        void pushState(State p_state);
        void popState();

        void handleEvents(Event& p_event);
        void update(Clock& p_clock);
        void draw(Window& p_window);
        
        FSM();
        ~FSM();

        template <class defaultState>
        FSM(defaultState&& f_ds) {
            Logger::log(INFO, "FSM created via move constructor.");
            init();
            m_states.emplace(std::move(f_ds));
            std::visit(
                [](auto &state){ state.init(); },
                m_states.top()
            ); 
        }

    private:
        std::stack<std::variant<T...>> m_states; 
        bool m_running;
    };

    // Default constructor.
    template <typename ...T>
    FSM<T...>::FSM() {
        Logger::log(ERROR, "Default FSM constructor called.");
        init();
    }

    // Destructor.
    template <typename ...T>
    FSM<T...>::~FSM() {
        Logger::log(INFO, "FSM destructor called.");
        cleanup();
    }

    // Initalize the state manager. 
    template <typename ...T>
    void FSM<T...>::init() {
        m_running = true;
        Logger::log(INFO, "FSM is now running.");
    }

    // Cleanup all states currently on the stack.
    // Mark machine as not running anymore.
    template <typename ...T>
    void FSM<T...>::cleanup() {
        // While there is still a state left, clean up resources and pop it.
        while(!m_states.empty()) {
            std::visit(
                [](auto& state){ state.cleanup(); },
                m_states.top()
            );
            m_states.pop();
        }
        m_running = false;
        Logger::log(INFO, "FSM was cleaned up.");
    }

    // Transition to a new state without preserving old one.
    template <typename ...T>
    void FSM<T...>::changeState(State p_state) {
        // Cleanup current state.
        if(!m_states.empty()) {
            std::visit(
                [](auto& state){ state.cleanup(); },
                m_states.top()
            );
            m_states.pop();
        }
        // Store and start up new state.
        m_states.emplace(std::move(p_state));
        std::visit(
            [](auto& state){ state.init(); },
            m_states.top()
        );
    }

    // Pause current state and switch to a new one.
    template <typename ...T>
    void FSM<T...>::pushState(State p_state) {
        // Pause current state.
        if(!m_states.empty()) {
            std::visit(
                [](auto& state){ state.pause(); },
                m_states.top()
            );
        }
        // Switch to new one and start it up.
        m_states.emplace(std::move(p_state));
        std::visit(
            [](auto& state){ state.init(); },
            m_states.top()
        );
    }

    // Cleanup current state and go back to previous state, resuming it.
    template <typename ...T>
    void FSM<T...>::popState() {
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
    void FSM<T...>::handleEvents(Event& p_event) {
        std::visit(
            [this, &p_event](auto& state){  state.handleEvents(*this, p_event); },
            m_states.top()
        );
    }

    // Let the state update info, actors, etc.
    template <typename ...T>
    void FSM<T...>::update(Clock& p_clock) {
        std::visit(
            [this, &p_clock](auto& state){ state.update(*this, p_clock); },
            m_states.top()
        );
    }

    // Let the state draw.
    template <typename ...T>
    void FSM<T...>::draw(Window& p_window) {
        std::visit(
            [this, &p_window](auto& state){ state.draw(*this, p_window); },
            m_states.top()
        );
    }
}