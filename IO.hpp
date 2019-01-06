#pragma once

/*
Handles the IO for the game, getting input and firing off signals.
*/

// Standard Headers.
#include <variant>

// Project Headers.
#include "Update.hpp"

namespace Engine {
    class Update;

    class IO {
    public:
        void init();
        void cleanup();

        void pause();
        void resume();

        Engine::Update onEvent();

        IO();
        ~IO();
    };
}
