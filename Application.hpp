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
#include "IO.hpp"
#include "Update.hpp"
#include "Render.hpp"
#include "Implementation.hpp"
// Standard Headers.
#include <variant>

namespace Game {
    class Application {
    public:
        Application(int p_windowWidth, int p_windowHeight, std::string p_applicationTitle, std::string p_applicationIcon);
        ~Application();

        void applicationLoop();

    private:
        // Window related items.
        sf::RenderWindow m_window;
        // Finite state machine for IO, Update and Render.
        Engine::FSM<Engine::IO, Engine::Update, Engine::Render> m_fsm;
        // Game states variant.
        std::variant<Game::Menu> m_game;
        sf::Image m_icon;
    };
}
