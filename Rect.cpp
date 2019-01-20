// Engine Headers.
#include "Rect.hpp"

namespace Game {
    Rect::Rect(int p_x, int p_y, int p_width, int p_height) : 
    m_x1 { p_x }, m_y1 { p_y }, m_x2 { p_x + p_width }, m_y2 { p_y + p_height } 
    {

    }

    Rect::~Rect() {

    }

    bool Rect::intersect(Rect& rect) {
        auto f_corners = rect.getCorners();
        if((m_x1 <= std::get<0>(f_corners)) && (m_y1 <= std::get<1>(f_corners)) && 
           (m_x2 <= std::get<2>(f_corners)) && (m_y2 <= std::get<2>(f_corners))) {
            return true;
        } else {
            return false;
        }
    }

	std::pair<int, int> Rect::getEdge() {
        return std::make_pair(m_x2, m_y2);
    }

    std::pair<int, int> Rect::getCenter() {
        int f_centerX = (m_x1 + m_x2) / 2;
        int f_centerY = (m_y1 + m_y2) / 2;
        return std::make_pair(f_centerX, f_centerY);
    }

    std::tuple<int, int, int, int> Rect::getCorners() {
        return std::make_tuple(m_x1, m_y1, m_x2, m_y2);
    }
}