// Project Headers.
#include "View.hpp"

namespace Engine {
    View::View(int p_x, int p_y, int p_width, int p_height) : 
    m_view { sf::FloatRect(p_x, p_y, p_width, p_height) } 
    {

    }

    View::~View() {

    }

    sf::View& View::getView() {
        return m_view;
    }
}