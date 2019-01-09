// Projects Headers.
#include "Window.hpp"

namespace Engine {
    Window::Window(int p_windowWidth, int p_windowHeight, std::string p_applicationTitle, std::string p_applicationIcon) : 
    m_window { sf::VideoMode(p_windowWidth, p_windowHeight), p_applicationTitle }
    {
        // Create the SFML icon and set it.
        m_icon.loadFromFile(p_applicationIcon);
        m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());
        Logger::log(INFO, "Created window and set icon.");
    }

    sf::RenderWindow& Window::getWindow() {
        return m_window;
    }
}