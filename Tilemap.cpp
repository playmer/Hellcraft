// Engine Headers.
#include "Tilemap.hpp"

namespace Game {
    Tilemap::Tilemap(int p_width, int p_length) {
        // Our level will be this size.
        m_map.reserve(p_width * p_length);
    }

    Tilemap::~Tilemap() {

    }

    std::vector<int>& Tilemap::getTilemap() {
        return m_map;
    }
}