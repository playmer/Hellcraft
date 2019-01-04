// Project Headers.
#include "Application.hpp"

namespace Game {
    // Constructor.
    Application::Application(int p_windowWidth, int p_windowHeight, std::string p_applicationTitle, std::string p_applicationIcon) {
        // Create the SFML window and related settings.
        m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(p_windowWidth, p_windowHeight), p_applicationTitle);
        m_icon.loadFromFile(p_applicationIcon);
        m_window->setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());
        // Create the game state machine, initalize to Menu state.
        m_game = std::make_unique<Engine::FSM<Game::Menu>>(Game::Menu{});
    }

    // Destructor.
    Application::~Application() {

    } 

    // Main application loop.
    void Application::applicationLoop() {
        while(m_window->isOpen()){
            // Used to capture events.
            sf::Event event;
            while(m_window->pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    m_window->close();
                }
                m_game->handleEvents();
                m_game->update();
            }
            m_window->clear();
            m_game->draw();
            m_window->display();
        }
    }
}