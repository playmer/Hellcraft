// Project Headers.
#include "Texture.hpp"

namespace Engine {
    Texture::Texture(const std::string& p_textureFile) {
        if(!m_texture.loadFromFile(p_textureFile)) {
            Logger::log(ERROR, p_textureFile + " could not be loaded!");
        }
    }

    Texture::Texture(const std::string& p_textureFile, int p_x, int p_y, int p_width, int p_height) {
        if(!m_texture.loadFromFile(p_textureFile)) {
            Logger::log(ERROR, p_textureFile + " could not be loaded with given dimensions!");
        }
    }

    Texture::~Texture() {

    }

    sf::Texture Texture::getTexture() const {
        return m_texture;
    }
}