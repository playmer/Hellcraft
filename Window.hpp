#pragma once

/*
Wrapper for SFML RenderWindow class so I can pass around events without murking up stuff from happening.
*/

// SFML Headers.
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
// Standard Headers.
#include <string>
// Project Headers.
#include "Log.hpp"

namespace Engine {
    class Window {
    public:
        Window(int p_windowWidth, int p_windowHeight, std::string p_applicationTitle, std::string p_applicationIcon);
        sf::RenderWindow& getWindow();
    
    private:
        sf::RenderWindow m_window;
        sf::Image m_icon;
    };
}