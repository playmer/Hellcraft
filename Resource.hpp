#pragma once

/*
Resource class that is used by the resource manager system.
*/

// Standard Headers.
#include <any>
#include <string>
#include <memory>
#include <unordered_map>

namespace Engine {
    template <typename T>
    class Resource {
    public:
        using Loader = std::shared_ptr<std::any> (*)(std::string);

        Resource(std::shared_ptr<std::any> p_data) : m_data { p_data }
        {

        }

        T& operator*() {
            return std::any_cast<T&>(*m_data);
        }

        T* operator->() {
            return std::any_cast<T&>(*m_data);
        }

        std::shared_ptr<std::any> m_data;
    };
}