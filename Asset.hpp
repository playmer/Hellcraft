#pragma once

/*
Just a virtual class pretty much as a base for my various game asset classes.
Used by resource management system.
*/

namespace Engine {
    class Asset {
    public:
        virtual ~Asset() = 0;
    };

    inline Asset::~Asset() = default; 
}