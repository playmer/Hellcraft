#pragma once

/*
Animation class to play, pause, loop, etc for sprites. Contains logic to create an animated sprite.
*/

// SFML Headers.
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
// Wrapper Headers.
#include "Clock.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"

namespace Engine {
    // Inherit from these SFML classes so we can have a custom draw function.
    class Animation : public sf::Drawable, public sf::Transformable {
    public:
        Animation();
        ~Animation();  
        
        // If we don't get anything input, we can assume these settings.
        void init(bool p_paused = false, bool p_looped = true);
        void setLooped(bool p_looped);
        void pause();
        void play();

    private:
        bool m_paused;
        bool m_looped; 
        // Is an override function so we can pass this classes objects into windows.draw().
        virtual void draw(sf::RenderTarget& p_target, sf::RenderStates& p_states);
    };
}