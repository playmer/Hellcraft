/*
Wrapper for SFML RenderWindow class so I can pass around events without murking up stuff from happening.
*/

// SFML Headers.
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
// Standard Headers.
#include <string>
// Project Headers.
#include "Log.hpp"

namespace Engine {
    class Window {
    public:
        Window(int p_windowWidth, int p_windowHeight, std::string p_applicationTitle, std::string p_applicationIcon);
        auto& getWindow();
    
    private:
        sf::RenderWindow m_window;
        sf::Image m_icon;
    };

    Window::Window(int p_windowWidth, int p_windowHeight, std::string p_applicationTitle, std::string p_applicationIcon) : 
    m_window {sf::VideoMode(p_windowWidth, p_windowHeight), p_applicationTitle }
    {
        // Create the SFML icon and set it.
        m_icon.loadFromFile(p_applicationIcon);
        m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());
        Logger::log(INFO, "Created window and set icon.");
    }

    auto& Window::getWindow() {
        return m_window;
    }
}