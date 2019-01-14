// Project Headers.
#include "Animation.hpp"
#include <string>

namespace Engine {
    Animation::Animation() {

    }

    Animation::~Animation() {

    }

    void Animation::init(const Texture& p_texture, bool p_paused, bool p_looped) {
        m_paused = p_paused;
        m_looped = p_looped;
        m_sprite.loadTexture(p_texture);
    }

    // Only goes for horizontal frames at the moment!
    void Animation::setFrames(int p_x, int p_y, int p_width, int p_height, int p_xsize, int p_ysize) {
        int f_frameCount = (p_width / p_xsize);
        for(int l_currentFrame = 0; l_currentFrame < f_frameCount; ++l_currentFrame) {
            m_frames.push_back(sf::IntRect((p_x) + (p_xsize * l_currentFrame), p_y, p_xsize, p_ysize));
        }
    }

    void Animation::setLooped(bool p_looped) {
        m_looped = p_looped;
    }

    void Animation::pause() {
        m_paused = true;
    } 

    void Animation::play() {
        m_paused = false;
    }

    void Animation::draw(sf::RenderTarget& p_target, sf::RenderStates p_states) const {

    }
}