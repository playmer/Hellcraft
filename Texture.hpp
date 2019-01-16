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
#include <any>
#include <string>
#include <memory>
// Project Headers.
#include "Log.hpp"
#include "Asset.hpp"

namespace Engine {
    class Texture : public Asset {
    public:
        Texture();
        ~Texture();
        
        // Loads partial file into a texture.
        void loadFile(const std::string& p_textureFile);

        const sf::Texture& getTexture() const;
        static std::shared_ptr<Asset> loadTexture(std::string p_textureFile);

    private:
        sf::Texture m_texture;
    };
}