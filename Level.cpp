// Game Headers.
#include "Level.hpp"

namespace Game {
    Level::Level(Engine::Manager* p_manager) : m_levelmap { p_manager } {

    }

    Level::~Level() {

    }

    Tilemap& Level::getMap() {
        return m_levelmap;
    }

    void Level::update(Engine::Clock& p_clock) {
        // Add more here later.
    }

    void Level::generateLevel(int p_width, int p_length) {
        // Create a new tilemap/level and display it.
        m_levelmap.init(p_width, p_length);
        m_levelmap.generate(p_width, p_length);
    }
}