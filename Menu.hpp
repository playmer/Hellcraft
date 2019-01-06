#pragma once

/*
Implements a Menu which is based off the State abstract class.
*/

// Project Headers.
#include "FSM.hpp"

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
        void handleEvents(FSM* p_fsm);
        template <typename FSM> 
        void update(FSM* p_fsm);
        template <typename FSM> 
        void draw(FSM* p_fsm);

        Menu();
        ~Menu();
    };

    Menu::Menu() {
        init();
    }

    Menu::~Menu() {
        cleanup();
    }

    void Menu::init() {

    }

    void Menu::cleanup() {

    }

    void Menu::pause() {

    }

    void Menu::resume() {

    }

    template <typename FSM> 
    void Menu::handleEvents(FSM* p_fsm) {

    }

    template <typename FSM> 
    void Menu::update(FSM* p_fsm) {

    }

    template <typename FSM> 
    void Menu::draw(FSM* p_fsm) {

    }
}