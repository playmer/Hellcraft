#pragma once

/*
State machine to manage game states and transitions.
Part of the game engine.
*/

// Standard Headers.
#include <stack>
// Project Headers.
#include "GS.hpp"

namespace Engine {
    // Forward declare class.
    class GS;

    class GSM {
    public:
        void init();
        void cleanup();

        void changeState(GS* state);
        void pushState(GS* state);
        void popState();

        void handleEvents();
        void update();
        void draw();

    private:
        std::stack<GS*> m_states; 
        bool m_running;
    };
}