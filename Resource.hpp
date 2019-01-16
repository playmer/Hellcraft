#pragma once

/*
Resource class that is used by the resource manager system.
*/

// Project Headers.
#include "Asset.hpp"
// Standard Headers.
#include <string>
#include <memory>
#include <unordered_map>

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
            return static_cast<T&>(*m_data);
        }

        std::shared_ptr<Asset> m_data;
    };
}