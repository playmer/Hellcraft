#pragma once

/*
Resource type class. Used in the resource manager system.
*/

// Standard Headers.
#include <any>
#include <string>
#include <memory>
#include <unordered_map>

namespace Engine {
    class Type {
    public:
        using Loader = std::shared_ptr<std::any> (*)(std::string);
        
        Type::Type(Loader p_function) : m_loader { p_function } {

        }
        
        Loader m_loader;
        std::unordered_map<std::string, std::shared_ptr<std::any>> m_resources;
    };
}