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

        double getTime();
        double getDeltaTime();
        double getCurrentTime();
        void addTimeStep();
        
    private:
        double m_time;
        double m_dt;
    };
}