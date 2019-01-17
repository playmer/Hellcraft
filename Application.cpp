// Engine Headers.
#include "Application.hpp"

namespace Game {
    // Constructor.
    Application::Application(int p_windowWidth, int p_windowHeight, std::string p_applicationTitle, std::string p_applicationIcon) : 
    m_window { p_windowWidth, p_windowHeight, p_applicationTitle, p_applicationIcon },
    m_game { Game::Menu{} }, m_clock { 1.0/60.0 }, m_view { 0, 0, p_windowWidth / 4, p_windowHeight / 4 }
    {
        m_window.getWindow().setView(m_view.getView());
    }

    // Destructor.
    Application::~Application() {
        Logger::log(INFO, "Destroyed game.");
    } 

    // Main application loop.
    void Application::applicationLoop() {
        // Set up game clock related stuff.
        double f_currentTime = Engine::Clock::getCurrentTime();
        double f_accumulator = 0.0;

        // Start game loop.
        while(m_window.getWindow().isOpen()){
            // Handle clock stuff.
            double f_newTime = Engine::Clock::getCurrentTime();
            double f_frameTime = f_newTime - f_currentTime;
            if(f_frameTime > 0.25) {
                f_frameTime = 0.25;
            } 
            f_currentTime = f_newTime;
            f_accumulator += f_frameTime;

            // Used to capture events, and fire signals in state based off them.
            Engine::Event f_event;
            while(m_window.getWindow().pollEvent(f_event.getEvent())) {
                // I really really hate the fact that this if statement exists here.. 
                // But I'll fix it up later.
                if(f_event.getEvent().type == sf::Event::Closed){
                    m_window.getWindow().close();
                }
                m_game.handleEvents(f_event);
            }

            // Handle more clock stuff then render after sending update.
            while(f_accumulator >= m_clock.getDeltaTime()) {
                m_game.update(m_clock);
                m_clock.setTime(m_clock.getTime() + m_clock.getDeltaTime());
                f_accumulator -= m_clock.getDeltaTime();
            }

            m_window.getWindow().clear();
            m_game.draw(m_window);
            m_window.getWindow().display();
        }
    }
}