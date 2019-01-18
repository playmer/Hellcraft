// Engine Headers.
#include "Tilemap.hpp"

namespace Game {
    Tilemap::Tilemap() {
        
    }

    Tilemap::~Tilemap() {

    }

    void Tilemap::init(int p_width, int p_length) {
        m_map.reserve(p_width * p_length);
        m_bsp.generateLevel(m_map, p_width, p_length);
    }

    void Tilemap::generate() {
        
    }

    std::vector<int>& Tilemap::getTilemap() {
        return m_map;
    }

    void Tilemap::printMap(int p_width, int p_length) {
        for(int x = 0; x < p_width; x++) {
            for(int y = 0; y < p_length; y++) {
                if(m_map[y * p_width + x] != Tiles::Empty) {
                    std::cout << "#";
                } else {
                    std::cout << ".";
                }
            }
            std::cout << std::endl;
        }
    }
}