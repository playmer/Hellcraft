#pragma once

/*
Resource class that is used by the resource manager system.
*/

// Standard Headers.
#include <memory>
#include <string>
#include <unordered_map>
// Engine Headers.
#include "Asset.hpp"

namespace Engine {
    template <typename T>
    class Resource {
    public:
        using Loader = std::shared_ptr<Asset> (*)(std::string);

        Resource(std::shared_ptr<Asset> p_data) : m_data { p_data }
        {

        }

        T& operator*() {
            return static_cast<T&>(*m_data);
        }

        T* operator->() {
            return &static_cast<T&>(*m_data);
        }

        std::shared_ptr<Asset> m_data;
    };
}