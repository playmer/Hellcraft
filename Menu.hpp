#pragma once

/*
Implements a Menu which is based off the State abstract class.
*/

// Project Headers.
#include "FSM.hpp"
// Wrapper Headers.
#include "Window.hpp"
#include "Event.hpp"
#include "Clock.hpp"

namespace Game {
    template <typename ...T>
    class FSM;

    class Menu {
    public:
        inline void init();
        inline void cleanup();

        inline void pause();
        inline void resume();

        template <typename FSM> 
        void handleEvents(FSM* p_fsm, const Engine::Event& p_event);
        template <typename FSM> 
        void update(FSM* p_fsm, const Engine::Clock& p_clock);
        template <typename FSM> 
        void draw(FSM* p_fsm, Engine::Window* p_window);
    };

    void Menu::init() {
        Logger::log(INFO, "Initializing menu.");
    }

    void Menu::cleanup() {
        Logger::log(INFO, "Cleaning up menu.");
    }

    void Menu::pause() {

    }

    void Menu::resume() {

    }

    template <typename FSM> 
    void Menu::handleEvents(FSM* p_fsm, const Engine::Event& p_event) {
        
    }

    template <typename FSM> 
    void Menu::update(FSM* p_fsm, const Engine::Clock& p_clock) {

    }

    template <typename FSM> 
    void Menu::draw(FSM* p_fsm, Engine::Window* p_window) {

    }
}