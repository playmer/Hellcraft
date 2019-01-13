#pragma once

/*
Clock class to hold onto deltatime and returns current time thanks to std::chrono.
*/

// Standard Headers.
#include <chrono>

namespace Engine {
    class Clock {
    public:
        Clock(double p_dt);
        ~Clock();

        void setTime(double p_time);
        double getTime() const;

        void setDeltaTime(double p_dt);
        double getDeltaTime() const;

        static double getCurrentTime();
        
    private:
        double m_time;
        double m_dt;
    };
}