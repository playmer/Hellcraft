// Project Headers.
#include "Clock.hpp"

namespace Engine {
    Clock::Clock(double p_dt) :
    m_time { 0.0 }, m_dt { p_dt } 
    {
        
    }

    Clock::~Clock() {
        
    }

    void Clock::setTime(double p_time) {
        m_time = p_time;
    }

    double Clock::getTime() {
        return m_time;
    }

    void Clock::setDeltaTime(double p_dt) {
        m_dt = p_dt;
    }

    double Clock::getDeltaTime() {
        return m_dt;
    }

    // Static function returns current time since epoch in ms as a double.
    double Clock::getCurrentTime() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
}