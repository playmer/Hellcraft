#pragma once

/*
Wrapper to allow us to easily load/create the different parts of our game,
as well as manage the other systems and keep various parts from interacting/
depending on each other if not needed.
*/

// SFML Headers.
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
// Project Headers.
#include "FSM.hpp"
#include "Menu.hpp"

namespace Game {
    class Application {
    public:
        Application(int p_windowWidth, int p_windowHeight, std::string p_applicationTitle, std::string p_applicationIcon);
        ~Application();

        void applicationLoop();

    private:
        // Window related items.
        sf::RenderWindow m_window;
        // Game state machine.
        Engine::FSM<Game::Menu> m_game;
        sf::Image m_icon;
    };
}