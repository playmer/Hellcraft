// Game Headers.
#include "Level.hpp"

namespace Game {
    Level::Level() {
        m_levelmap.init(100, 100);
        m_levelmap.printMap(100, 100);
    }

    Level::~Level() {

    }

    Tilemap& Level::getMap() {
        return m_levelmap;
    }

    void update(Engine::Clock& p_clock) {
        // Add more here later.
    }
}