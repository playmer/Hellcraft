#pragma once

/*
Abstract interface of the game states.
Part of the game engine.
*/

namespace Engine {
    class GS {
        public:
            virtual void init() = 0;
            virtual void cleanup() = 0;

            virtual void pause() = 0;
            virtual void resume() = 0;

            virtual void handleEvents() = 0;
            virtual void update() = 0;
            virtual void draw() = 0;
    };
}