// Project Headers.
#include "Texture.hpp"

namespace Engine {
    Texture::Texture() {
        
    }

    void Texture::loadFile(const std::string& p_textureFile) {
        if(!m_texture.loadFromFile(p_textureFile)) {
            Logger::log(ERROR, p_textureFile + " could not be loaded!");
        }
    }

    Texture::~Texture() {
        
    }

    const sf::Texture& Texture::getTexture() const {
        return m_texture;
    }

    std::shared_ptr<std::any> Texture::loadTexture(std::string p_textureFile) {
        auto f_texture = std::make_shared<std::any>();
        auto& f_textureReference = std::any_cast<Texture&>(*f_texture);
        f_textureReference.loadFile(p_textureFile);
        return f_texture;
    }
}