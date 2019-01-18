#pragma once

/*
Class that is used to create/hold the binary search tree and translate into the vector format
that our tilemap class needs.
*/

// Standard Headers.
#include <memory>
#include <tuple>
#include <vector>
#include <utility>
// Game Headers.
#include "Leaf.hpp"
#include "Rect.hpp"
#include "RNG.hpp"
#include "Tiles.hpp"

namespace Game {
    class BSP {
    public:
        BSP();
        ~BSP();

        void generateLevel(std::vector<int>& p_map, int p_mapWidth, int p_mapHeight);
        void createRoom(Rect& p_room);
        void createHall(Rect& p_roomA, Rect& p_roomB);
        void cleanUpMap(int p_mapWidth, int p_mapHeight);
        int getAdjacentWallCount(int p_x, int p_y);
        int getMinRoomSize();
        int getMaxRoomSize();

    private:
        int m_mapWidth, m_mapHeight;
        int m_maxLeafSize;
        int m_minRoomSize, m_maxRoomSize;
        bool m_smoothEdges;
        int m_smoothingFactor;
        int m_fillingFactor;

        std::vector<int> m_bspMap;
    };
}