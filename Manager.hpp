#pragma once

/*
Resource manager class to handle all loading/unloading of various resources that can be shared.
Such as textures, sounds, fonts and the like. Sprites aren't shared, but load from same texture.
Uses templates under the hood to accomplish this in a generic way.
*/

// Standard Headers.
#include <unordered_map>

namespace Engine {
    class Manager {
    public:
    private:
    };
}