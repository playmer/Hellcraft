// Project Headers.
#include "Sprite.hpp"

namespace Engine {
    Sprite::Sprite() {

    }

    Sprite::Sprite(const Texture& p_texture) {
        Logger::log(DEBUG, "Sprite with param-constructor called.");
        loadTexture(p_texture);
    }

    Sprite::~Sprite() {
        Logger::log(DEBUG, "Sprite destroyed!");
    }

    void Sprite::loadTexture(const Texture& p_texture) {
        Logger::log(DEBUG, "Sprite loaded with texture.");
        m_sprite.setTexture(p_texture.getTexture());
    }

    void Sprite::setTextureRect(int p_x, int p_y, int p_width, int p_height) {
        m_sprite.setTextureRect(sf::IntRect(p_x, p_y, p_width, p_height));
    }

    void Sprite::setColour(int p_r, int p_g, int p_b, int p_alpha) {
        m_sprite.setColor(sf::Color(p_r, p_g, p_b, p_alpha));
    }

    const sf::Sprite& Sprite::getSprite() const {
        return m_sprite;
    }
}