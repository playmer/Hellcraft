#pragma once

/*
Wrapper class for the SFML view class.
*/

// SFML Headers.
#include <SFML/Graphics/View.hpp>

namespace Engine {
    class View {
    public:
        View(int p_x, int p_y, int p_width, int p_height);
        ~View();

        sf::View& getView();

    private:
        sf::View m_view;
    };
}