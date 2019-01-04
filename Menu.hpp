#pragma once

/*
Implements a Menu which is based off the State abstract class.
*/

// Project Headers.
#include "GS.hpp"

namespace Game {
    class Menu : Engine::GS {
        public:
            void init() override;
            void cleanup() override;

            void pause() override;
            void resume() override;

            void handleEvents() override;
            void update() override;
            void draw() override;
    };
}