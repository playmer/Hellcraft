#pragma once

/*
Used to create and hold the tilemap for this game. Basically an area of integers describing stuff.
Also includes dungeon generation features. Map is basically a massive grid.
*/

// SFML Headers.
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace Game {
    class Tilemap : public sf::Drawable, public sf::Transformable {
    public:
        Tilemap();
        ~Tilemap();

    private:
        virtual void draw(sf::RenderTarget& m_target, sf::RenderStates m_states) const;
    };
}