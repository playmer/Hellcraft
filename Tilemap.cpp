// Engine Headers.
#include "Tilemap.hpp"

namespace Game {
    Tilemap::Tilemap() {
        
    }

    Tilemap::~Tilemap() {

    }

    void Tilemap::init(int p_width, int p_length) {
        m_map.reserve(p_width * p_length);
    }

    std::vector<int>& Tilemap::getTilemap() {
        return m_map;
    }
}