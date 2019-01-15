#pragma once

/*
Wrapper class that creates and loads an image into a texture.
Also scales/rotates/transforms the texture as needed.
Used so we can use the same texture on multiple sprites as well as
locations to save on the memory foot print.
*/

// SFML Headers.
#include <SFML/Graphics/Texture.hpp>
// Standard Headers.
#include <string>
#include <any>
#include <memory>
// Project Headers.
#include "Log.hpp"

namespace Engine {
    class Texture {
    public:
        Texture();
        ~Texture();
        
        // Loads partial file into a texture.
        void loadFile(const std::string& p_textureFile, int p_x, int p_y, int p_width, int p_height);

        const sf::Texture& getTexture() const;
        static std::shared_ptr<std::any> loadTexture(const std::string& p_textureFile, int p_x, int p_y, int p_width, int p_height);

    private:
        sf::Texture m_texture;
    };
}