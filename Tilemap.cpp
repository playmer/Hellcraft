// Engine Headers.
#include "Tilemap.hpp"

namespace Game {
    Tilemap::Tilemap(Engine::Manager* p_manager) : m_manager { p_manager } {
        
    }

    Tilemap::~Tilemap() {

    }

    void Tilemap::init(int p_width, int p_length) {
        m_map.reserve(p_width * p_length);
    }

    void Tilemap::generate(int p_width, int p_length) {
        m_bsp.generateLevel(m_map, p_width, p_length);
        createVertexArray(sf::Vector2u(32, 32), p_width, p_length);
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

    void Tilemap::createVertexArray(sf::Vector2u p_tileSize, int p_width, int p_length) {
        // Resize vertex array.
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(p_width * p_length * 4);
        // Populate vertex array with one quad per tile.
        for(int l_x = 0; l_x < p_width; l_x++) {
            for(int l_y = 0; l_y < p_length; l_y++) {
                // Get our Tile ID;
                auto f_tileID = m_map[p_width * l_y + l_x];
                int f_tu, f_tv;
                if(f_tileID == Tiles::Empty) {
                    f_tu = 208; // Will be used later scriptwise, hardcoded for now.
                    f_tv = 224;
                } else if(f_tileID == Tiles::Floor) {
                    f_tu = 16;
                    f_tv = 64;
                }
                // Get a pointer to the current tile's quad.
                sf::Vertex* f_quad = &m_vertices[(p_width * l_y + l_x) * 4];
                // Define corners.
                f_quad[0].position = sf::Vector2f(l_x * p_tileSize.x, l_y * p_tileSize.y);
                f_quad[1].position = sf::Vector2f((l_x + 1) * p_tileSize.x, l_y * p_tileSize.y);
                f_quad[2].position = sf::Vector2f((l_x + 1) * p_tileSize.x, (l_y + 1) * p_tileSize.y);
                f_quad[3].position = sf::Vector2f(l_x * p_tileSize.x, (l_y + 1) * p_tileSize.y);
                // Define texture coordinates.
                f_quad[0].texCoords = sf::Vector2f(f_tu * p_tileSize.x, f_tv * p_tileSize.y);
                f_quad[1].texCoords = sf::Vector2f((f_tu + 1) * p_tileSize.x, f_tv * p_tileSize.y);
                f_quad[2].texCoords = sf::Vector2f((f_tu + 1) * p_tileSize.x, (f_tv + 1) * p_tileSize.y);
                f_quad[3].texCoords = sf::Vector2f(f_tu * p_tileSize.x, (f_tv + 1) * p_tileSize.y);
            }
        }
    }

    // Is an override function so we can pass this classes objects into windows.draw().
    void Tilemap::draw(sf::RenderTarget& p_target, sf::RenderStates p_states) const {
        // Apply tileset texture.
        p_states.texture = &m_manager->getResource<Engine::Texture>("Tileset")->getTexture();
        // Draw vertex array.
        p_target.draw(m_vertices, p_states);
    }
}

