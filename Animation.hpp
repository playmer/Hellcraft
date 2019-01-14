#pragma once

/*
Animation class to play, pause, loop, etc for sprites. Contains logic to create an animated sprite.
*/

// Project Headers.
#include "Log.hpp"
// SFML Headers.
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
// Wrapper Headers.
#include "Clock.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
// Standard Headers.
#include <vector>

namespace Engine {
    // Inherit from these SFML classes so we can have a custom draw function.
    class Animation : public sf::Drawable, public sf::Transformable {
    public:
        Animation();
        ~Animation();  
        
        // If we don't get anything input, we can assume these settings.
        void init(const Texture& p_texture, bool p_paused = false, bool p_looped = true);
        // Automatically divide into frames and add to vector.
        void cutFrames(int p_x, int p_y, int p_width, int p_height, int p_xsize, int p_ysize);
        void setLooped(bool p_looped);

        void pause();
        void play();

        // Set to the frame number we just received.
        void setFrame(int p_frameNumber);

    private:
        bool m_paused;
        bool m_looped;

        Sprite m_sprite;

        int m_frameCount;
        int m_currentFrameNumber;
        std::vector<sf::IntRect> m_frames;
        // Is an override function so we can pass this classes objects into windows.draw().
        virtual void draw(sf::RenderTarget& p_target, sf::RenderStates p_states) const; 
    };
}