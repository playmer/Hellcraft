#pragma once

/*
Abstract interface of the game states.
Part of the game engine.
*/

// Project Headers.
#include "GSM.hpp"

namespace Engine {
    // Forward declare class.
    class GSM;

    class GS {
        public:
            virtual void init() = 0;
            virtual void cleanup() = 0;

            virtual void pause() = 0;
            virtual void resume() = 0;

            virtual void handleEvents(GSM* manager) = 0;
            virtual void update(GSM* manager) = 0;
            virtual void draw(GSM* manager) = 0;
    };
}