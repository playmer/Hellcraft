#pragma once

/*
Helper class for BSP generation of dungeon tilemap.
*/

// Standard Headers.
#include <memory>
#include <random>
#include <optional>
// Game Headers
#include "BSP.hpp"
#include "Rect.hpp"

namespace Game {
    class Leaf {
    public:
        Leaf(int p_x, int p_y, int p_width, int p_height);
        ~Leaf();
        
        bool splitLeaf();
        void createRooms(BSP& p_bsp);
        std::optional<std::reference_wrapper<Rect>> getRoom();

    private:
        int m_x, m_y;
        int m_width, m_height;
        int m_minLeafSize;
        
        std::unique_ptr<Leaf> m_childA, m_childB;
        std::unique_ptr<Rect> m_room, m_hall;

        std::random_device m_rd;
        std::mt19937 m_rng;
        std::uniform_int_distribution<int> m_randomBool;
    };
}