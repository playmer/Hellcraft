// Project Headers.
#include "Event.hpp"

namespace Engine {
    Event::Event() : m_event {} {

    }

    sf::Event& Event::getEvent() {
        return m_event;
    }
}