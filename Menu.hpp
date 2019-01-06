#pragma once

/*
Implements a Menu which is based off the State abstract class.
*/

// Standard Headers.
#include <variant>

namespace Game {
    class Menu {
    public:
        void init();
        void cleanup();

        void pause();
        void resume();

        std::variant onEvent();

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

    std::variant Menu::onEvent() {

    }
}