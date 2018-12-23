/*
State machine to manage game states and transitions.
Part of the game engine.
*/

// Project Headers.
#include "GSM.hpp"
#include "GS.hpp"

namespace Engine {
    // Initalize the state manager.
    void GSM::init() {
        m_running = true;
    }

    // Cleanup all states currently on the stack.
    // Mark machine as not running anymore.
    void GSM::cleanup() {
        // While there is still a state left, clean up resources and pop it.
        while(!m_states.empty()) {
            m_states.top()->cleanup();
            m_states.pop();
        }
        m_running = false;
    }

    // Transition to a new state without preserving old one.
    void Engine::GSM::changeState(GS* state) {
        // Cleanup current state.
        if(!m_states.empty()) {
            m_states.top()->cleanup();
            m_states.pop();
        }
        // Store and start up new state.
        m_states.push(state);
        m_states.top()->init();
    }

    // Pause current state and switch to a new one.
    void GSM::pushState(GS* state) {
        // Pause current state.
        if(!m_states.empty()) {
            m_states.top()->pause();
        }
        // Switch to new one and start it up.
        m_states.push(state);
        m_states.top()->init();
    }

    // Cleanup current state and go back to previous state, resuming it.
    void GSM::popState() {
        // Cleanup current state.
        if(!m_states.empty()) {
            m_states.top()->cleanup();
            m_states.pop();
        }
        // Resume previous state.
        if(!m_states.empty()) {
            m_states.top()->resume();
        }
    }

    // Let the state handle events.
    void GSM::handleEvents() {
        m_states.top()->handleEvents(this);
    }

    // Let the state update info, actors, etc.
    void GSM::update() {
        m_states.top()->update(this);
    }

    // Let the state draw.
    void GSM::draw() {
        m_states.top()->draw(this);
    }
}