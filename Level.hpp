#pragma once

/*
Game specific code to handle levels, the tilemap, flags of certain events and other parts related to
handling level creation and management in game.
*/

// Game Headers.
#include "Tilemap.hpp"

namespace Game {
    class Level {
    public:
        Level();
        ~Level();

    private:
        Tilemap m_map;
    };
}