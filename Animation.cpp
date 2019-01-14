// Project Headers.
#include "Animation.hpp"

namespace Engine {
    Animation::Animation() {

    }

    Animation::~Animation() {

    }

    void Animation::init(bool p_paused = false, bool p_looped = true) {
        m_paused = p_paused;
        m_looped = p_looped;
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
}