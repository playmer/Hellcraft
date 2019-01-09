// Project Headers.
#include "Application.hpp"

namespace Game {
    // Constructor.
    Application::Application(int p_windowWidth, int p_windowHeight, std::string p_applicationTitle, std::string p_applicationIcon) : 
    m_window { p_windowWidth, p_windowHeight, p_applicationTitle, p_applicationIcon },
    m_game { Game::Menu{} }
    {
        
    }

    // Destructor.
    Application::~Application() {
        Logger::log(INFO, "Destroyed game.");
    } 

    // Main application loop.
    void Application::applicationLoop() {
        while(m_window.getWindow().isOpen()){
            // Used to capture events.
            Engine::Event f_event;
            while(m_window.getWindow().pollEvent(f_event.getEvent())) {
                m_game.handleEvents(f_event);
                m_game.update();
            }
            m_window.getWindow().clear();
            m_game.draw(m_window);
            m_window.getWindow().display();
        }
    }
}