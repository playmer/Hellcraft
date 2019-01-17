#pragma once

/*
Resource type class. Used in the resource manager system.
*/

// Standard Headers.
#include <memory>
#include <string>
#include <unordered_map>
// Engine Headers.
#include "Asset.hpp"

namespace Engine {
    class Type {
    public:
        using Loader = std::shared_ptr<Asset> (*)(std::string);
        
        Type(Loader p_function) : m_loader { p_function } {

        }
        
        Loader m_loader;
        std::unordered_map<std::string, std::shared_ptr<Asset>> m_resources;
    };
}