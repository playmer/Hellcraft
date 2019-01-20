// Game Headers.
#include "Level.hpp"

namespace Game {
    Level::Level() {
        m_levelmap.init(50, 50);
        m_levelmap.generate(50, 50);
        m_levelmap.printMap(50, 50);
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