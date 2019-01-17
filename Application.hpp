#pragma once

/*
Wrapper to allow us to easily load/create the different parts of our game,
as well as manage the other systems and keep various parts from interacting/
depending on each other if not needed.
*/

// Engine Headers.
#include "Clock.hpp"
#include "Event.hpp"
#include "FSM.hpp"
#include "Log.hpp"
#include "View.hpp"
#include "Window.hpp"
// Game Headers.
#include "GS.hpp"
#include "Menu.hpp"

namespace Game {
    class Application {
    public:
        Application(int p_windowWidth, int p_windowHeight, std::string p_applicationTitle, std::string p_applicationIcon);
        ~Application();

        void applicationLoop();

    private:
        // Window related items.
        Engine::Window m_window;
        // Game state machine.
        Engine::FSM<Game::Menu, Game::GS> m_game;
        // Game clock.
        Engine::Clock m_clock;
        // Game view.
        Engine::View m_view;
    };
}