// Project Headers.
#include "Animation.hpp"

namespace Engine {
    Animation::Animation() {

    }

    Animation::~Animation() {

    }

    void Animation::init(const Texture& p_texture, double p_frameTime, bool p_paused, bool p_looped) {
        m_paused = p_paused;
        m_looped = p_looped;
        m_sprite.loadTexture(p_texture);
        m_frameTime = p_frameTime;
        m_currentTime = 0.0;
        m_currentFrameNumber = 0;
    }

    // Only goes for horizontal frames at the moment!
    // Remember this is cutting the texture only, so use that as a reference.
    void Animation::cutFrames(int p_x, int p_y, int p_width, int p_height, int p_xsize, int p_ysize) {
        m_frameCount = (p_width / p_xsize);
        for(int l_currentFrame = 0; l_currentFrame < m_frameCount; ++l_currentFrame) {
            m_frames.push_back(sf::IntRect((p_xsize * l_currentFrame), p_y, p_xsize, p_ysize));
        }
    }

    void Animation::setLooped(bool p_looped) {
        m_looped = p_looped;
    }

    void Animation::update(const Clock& p_clock) {
        if(!m_paused) {
            m_currentTime += p_clock.getDeltaTime();
            if(m_currentTime >= m_frameTime) {
                m_currentTime = remainder(m_currentTime, m_frameTime);
                if((m_currentFrameNumber + 1) < m_frameCount) {
                    m_currentFrameNumber++;
                } else {
                    m_currentFrameNumber = 0;
                    if(!m_looped) {
                        m_paused = true;
                    }
                }
                setFrame(m_currentFrameNumber);
            }
        }
    }

    void Animation::pause() {
        m_paused = true;
    } 

    void Animation::play() {
        m_paused = false;
    }

    void Animation::setFrame(int p_frameNumber) {
        m_sprite.setTextureRect(m_frames[p_frameNumber]);
    }

    void Animation::draw(sf::RenderTarget& p_target, sf::RenderStates p_states) const {
        p_target.draw(m_sprite.getSprite());
    }
}