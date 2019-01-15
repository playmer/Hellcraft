#pragma once

/*
Resource manager class to handle all loading/unloading of various resources that can be shared.
Such as textures, sounds, fonts and the like. Sprites aren't shared, but load from same texture.
Uses templates under the hood to accomplish this in a generic way.
*/

// Standard Headers.
#include <any>
#include <string>
#include <memory>
#include <unordered_map>
// Project Headers.
#include "Type.hpp"
#include "Resource.hpp"

namespace Engine {
    class Manager {
    public:
        using Loader = std::shared_ptr<std::any> (*)(std::string);

        template<typename T> 
        void addResource(std::string p_resourceName);
        template<typename T> 
        void addResourceType(Loader p_function);
        template<typename T>
        Resource<T> getResource(std::string p_resourceName);

    private:
        std::unordered_map<std::string, Type> m_types;
    };

    template<typename T> 
    void Manager::addResource(std::string p_resourceName) {
        auto f_it = m_types.find(typeid(T).name());
        if(f_it != m_types.end()) {
            auto& f_type = f_it->second;
            f_type.m_resources.emplace(p_resourceName, std::move(f_type.m_loader(p_resourceName)));
        }
    }

    template<typename T> 
    void Manager::addResourceType(Loader p_function) {
        Type f_typeLoader{ p_function };
        m_types.emplace(typeid(T).name(), f_typeLoader);
    }

    template<typename T>
    Resource<T> Manager::getResource(std::string p_resourceName) {
        auto f_it = m_types.find(typeid(T).name());
        if(f_it != m_types.end()) {
            auto& f_type = f_it->second;
            auto f_resourceIt = f_type.m_resources.find(p_resourceName);
            if(f_resourceIt != f_type.m_resources.end()) {
                return Resource<T>{ f_resourceIt->second };
            }
        }
        return Resource<T> { nullptr };
    }
}