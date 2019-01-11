// Project Headers.
#include "Clock.hpp"

namespace Engine {
    Clock::Clock(int p_dt) :
    m_time { 0.0 }, m_dt { p_dt } 
    {
        
    }

    double Clock::getTime() {
        return m_time;
    }

    double Clock::getDeltaTime() {
        return m_dt;
    }

    // Returns current time since epoch in ms.
    double Clock::getCurrentTime() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    // Adds the delta to our time member.
    void Clock::addTimeStep() {
        m_time += m_dt;
    }
}