#pragma once

/*
Wrapper for SFML Event class so I can pass around events without murking up stuff from happening.
*/

// SFML Headers.
#include <SFML/Window/Event.hpp>

namespace Engine {
    class Event {
    public:
        Event();
        auto getEvent();
        void setEvent(sf::Event p_event);

    private:
        sf::Event m_event;
    };

    Event::Event() : m_event {} {

    }

    auto Event::getEvent() {
        return m_event;
    }

    void Event::setEvent(sf::Event p_event) {
        m_event = p_event;
    }
}