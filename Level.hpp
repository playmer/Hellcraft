#pragma once

/*
Game specific code to handle levels, the tilemap, flags of certain events and other parts related to
handling level creation and management in game.
*/

// Engine Headers.
#include "Clock.hpp"
// Game Headers.
#include "Tilemap.hpp"

namespace Game {
    class Level {
    public:
        Level();
        ~Level();

        // Returns a reference to the map so we can draw it in current state.
        Tilemap& getMap();
        // Update function to update level events for animation wise.
        void update(Engine::Clock& p_clock);

    private:
        Tilemap m_levelmap;
    };
}