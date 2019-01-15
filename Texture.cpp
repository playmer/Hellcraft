// Project Headers.
#include "Texture.hpp"

namespace Engine {
    Texture::Texture() {
        
    }

    void Texture::loadFile(const std::string& p_textureFile, int p_x, int p_y, int p_width, int p_height) {
        if(!m_texture.loadFromFile(p_textureFile, sf::Rect(p_x, p_y, p_width, p_height))) {
            Logger::log(ERROR, p_textureFile + " could not be loaded with given dimensions!");
        }
    }

    Texture::~Texture() {
        
    }

    const sf::Texture& Texture::getTexture() const {
        return m_texture;
    }

    std::shared_ptr<std::any> Texture::loadTexture(const std::string& p_textureFile, int p_x, int p_y, int p_width, int p_height) {
        auto f_texture = std::make_shared<std::any>();
        auto& f_textureReference = std::any_cast<Texture&>(*f_texture);
        f_textureReference.loadFile(p_textureFile, p_x, p_y, p_width, p_height);
        return f_texture;
    }
}