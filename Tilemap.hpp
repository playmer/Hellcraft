#pragma once

/*
Used to create and hold the tilemap for this game. Basically an area of integers describing stuff.
Also includes dungeon generation features. Map is basically a massive grid held in a 1D vector.
*/

// SFML Headers.
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
// Standard Headers.
#include <string>
#include <vector>
// Engine Headers.
#include "Log.hpp"
#include "Manager.hpp"
#include "Texture.hpp"
// Game Headers.
#include "BSP.hpp"
#include "Leaf.hpp"
#include "Rect.hpp"
#include "Tiles.hpp"

namespace Game {
    class Tilemap : public sf::Drawable, public sf::Transformable {
    public:
        // When we make tilemap, we need to make it a certain size.
        Tilemap(Engine::Manager* p_manager);
        ~Tilemap();

        void init(int p_width, int p_length);
        void printMap(int p_width, int p_length);
        void generate(int p_width, int p_length);

        std::vector<int>& getTilemap();

    private:
        // Function to create a vertex array.
        void createVertexArray(sf::Vector2u p_tileSize, int p_width, int p_length);
        // Is an override function so we can pass this classes objects into windows.draw().
        virtual void draw(sf::RenderTarget& p_target, sf::RenderStates p_states) const; 

        BSP m_bsp;
        std::vector<int> m_map;
        Engine::Manager* m_manager;
        
        sf::VertexArray m_vertices;
    };
}