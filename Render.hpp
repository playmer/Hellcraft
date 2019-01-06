#pragma once

/*
Handles all the rendering for the game.
*/

// Standard Headers.
#include <variant>

// Project Headers.
#include "IO.hpp"

namespace Engine {
    class IO;

    class Render {
    public:
        void init();
        void cleanup();

        void pause();
        void resume();

        Engine::IO onEvent();

        Render();
        ~Render();
    };
}