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
        sf::Event& getEvent();

    private:
        sf::Event m_event;
    };
}