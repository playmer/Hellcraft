#pragma once

/*
Handles the updating for the game.
*/

// Standard Headers.
#include <variant>

// Project Headers.
#include "Render.hpp"

namespace Engine {
    class Render;

    class Update {
    public:
        void init();
        void cleanup();

        void pause();
        void resume();

       Engine::Render onEvent();

        Update();
        ~Update();
    };
}