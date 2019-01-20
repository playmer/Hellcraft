#pragma once

/*
Game specific code to handle levels, the tilemap, flags of certain events and other parts related to
handling level creation and management in game.
*/

// Engine Headers.
#include "Clock.hpp"
#include "Manager.hpp"
// Game Headers.
#include "Tilemap.hpp"

namespace Game {
    class Level {
    public:
        Level(Engine::Manager* p_manager);
        ~Level();

        // Returns a reference to the map so we can draw it in current state.
        Tilemap& getMap();
        // Update function to update level events for animation wise.
        void update(Engine::Clock& p_clock);
        void generateLevel(int p_width, int p_length);

    private:
        Tilemap m_levelmap;
    };
}