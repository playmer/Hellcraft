#pragma once

/*
Sprite class to hold a texture for a sprite. Can be either a single frame or multiple frames.
If multiple frames the Animation class will break texture up, process into frames and play it.
*/

// Project Headers.
#include "Log.hpp"
// SFML Headers.
#include <SFML/Graphics/Sprite.hpp>
// Wrapper Headers.
#include "Texture.hpp"

namespace Engine {
    class Sprite {
    public:
        Sprite();
        Sprite(const Texture& p_texture);
        ~Sprite();
        
        void loadTexture(const Texture& p_texture);
        void setTextureRect(int p_x, int p_y, int p_width, int p_height);
        void setColour(int p_r, int p_g, int p_b, int p_alpha);
        // Returns a reference to sprite.
        const sf::Sprite& getSprite() const;

    private:
        sf::Sprite m_sprite;
    };
}