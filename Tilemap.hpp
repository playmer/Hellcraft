#pragma once

/*
Used to create and hold the tilemap for this game. Basically an area of integers describing stuff.
Also includes dungeon generation features. Map is basically a massive grid held in a 1D vector.
*/

// Standard Headers.
#include <vector>
// Game Headers.
#include "Tiles.hpp"

namespace Game {
    class Tilemap {
    public:
        // When we make tilemap, we need to make it a certain size.
        Tilemap(int p_width, int p_length);
        ~Tilemap();

        std::vector<int>& getTilemap();

    private:
        // Generates the actual tilemap with all the needed values.
        void generateTilemap();

        std::vector<int> m_map;
    };
}