// Game Headers.
#include "Level.hpp"

namespace Game {
    Level::Level() {

    }

    Level::~Level() {

    }

    Tilemap& Level::getMap() {
        return m_map;
    }

    void update(Engine::Clock& p_clock) {
        // Add more here later.
    }
}