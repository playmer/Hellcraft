#pragma once

/*
Just a virtual class pretty much..
*/

namespace Engine {
    class Asset {
    public:
        virtual ~Asset() = default;
    protected:
        Asset() = default;
    };
}