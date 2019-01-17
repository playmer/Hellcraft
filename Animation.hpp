#pragma once

/*
Animation class to play, pause, loop, etc for sprites. Contains logic to create an animated sprite.
*/

// SFML Headers.
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
// Standard Headers.
#include <cmath>
#include <vector>
// Engine Headers.
#include "Clock.hpp"
#include "Log.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"

namespace Engine {
    // Inherit from these SFML classes so we can have a custom draw function.
    class Animation : public sf::Drawable, public sf::Transformable {
    public:
        Animation();
        ~Animation();  
        
        // If we don't get anything input, we can assume these settings.
        void init(const Texture& p_texture, double p_frameTime, bool p_paused = false, bool p_looped = true);
        // Automatically divide into frames and add to vector.
        void cutFrames(int p_x, int p_y, int p_width, int p_height, int p_xsize, int p_ysize);
        void setLooped(bool p_looped);

        void update(Clock& p_clock);
        void pause();
        void play();

        // Set to the frame number we just received.
        void setFrame(int p_frameNumber);

    private:
        bool m_paused;
        bool m_looped;
        
        Sprite m_sprite;

        double m_currentTime;
        double m_frameTime;

        int m_frameCount;
        int m_currentFrameNumber;
        std::vector<sf::IntRect> m_frames;
        // Is an override function so we can pass this classes objects into windows.draw().
        virtual void draw(sf::RenderTarget& p_target, sf::RenderStates p_states) const; 
    };
}