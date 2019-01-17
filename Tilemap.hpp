#pragma once

/*
Used to create and hold the tilemap for this game. Basically an area of integers describing stuff.
Also includes dungeon generation features. Map is basically a massive grid held in a 1D vector.
*/

// Standard Headers.
#include <vector>

namespace Game {
    class Tilemap {
    public:
        // When we make tilemap, we need to make it a certain size.
        Tilemap(int p_width, int p_length);
        ~Tilemap();

        std::vector<int>& getTilemap();

    private:
        std::vector<int> m_map;
    };
}