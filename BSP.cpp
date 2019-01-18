// Game Headers.
#include "BSP.hpp"

namespace Game {
    BSP::BSP() : m_maxLeafSize { 24 }, m_minRoomSize { 6 }, m_maxRoomSize { 15 },
    m_smoothEdges { true }, m_smoothingFactor { 1 }, m_fillingFactor { 3 } 
    {

    }

    BSP::~BSP() {

    }

    void BSP::generateLevel(std::vector<int>& p_map, int p_mapWidth, int p_mapHeight) {
        // Create empty 1D "2D vector that we'll end up assigning the p_map to."
        m_mapWidth = p_mapWidth;
        m_mapHeight = p_mapHeight;
        m_bspMap.reserve(p_mapWidth * p_mapHeight);
        for(int l_x = 0; l_x < m_mapWidth; ++l_x) {
            for(int l_y = 0; l_y < m_mapHeight; ++l_y) {
                m_bspMap[m_mapWidth * l_x + l_y] = Tiles::Empty;
            }
        }

        // Create a vector of leafs.
        std::vector<Leaf> f_leaves;
        auto f_rootLeaf = Leaf(0, 0, p_mapWidth, p_mapHeight);
        f_leaves.emplace_back(std::move(f_rootLeaf));

        // Keep looping until nothing can be split anymore.
        bool f_splitSuccessfully = true;
        while(f_splitSuccessfully) {
            f_splitSuccessfully = false;
            for(auto& l_leaf : f_leaves) {
                if(!l_leaf.returnChildA() && !l_leaf.returnChildB()) {
                    std::uniform_int_distribution<int> f_dist(0, 10);
                    if(l_leaf.getWidth() > m_maxLeafSize || l_leaf.getHeight() > m_maxLeafSize || f_dist(g_rng) > 8) {
                        if(l_leaf.splitLeaf()){
                            f_leaves.emplace_back(l_leaf.returnChildA());
                            f_leaves.emplace_back(l_leaf.returnChildB());
                            f_splitSuccessfully = true;
                        }
                    } 
                }
            }
        }

        // Create rooms.
        f_rootLeaf.createRooms(*this);
        // Cleanup map.
        cleanUpMap(m_mapWidth, m_mapHeight);

        // Done. Assign our BSP map to the actual tileset map that was passed in and be done with it.   
        p_map = m_bspMap;
    }

    void BSP::createRoom(Rect& p_room) {
        for(int l_x = (std::get<0>(p_room.getCorners()) + 1); l_x < std::get<2>(p_room.getCorners()); ++l_x) {
            for(int l_y = (std::get<1>(p_room.getCorners()) + 1); l_y < std::get<3>(p_room.getCorners()); ++l_y) {
                m_bspMap[m_mapWidth * l_x + l_y] = Tiles::Floor;
            }
        }
    }

    void BSP::createHall(Rect& p_roomA, Rect& p_roomB) {

    }

    void BSP::cleanUpMap(int p_mapWidth, int p_mapHeight) {

    }

    int BSP::getAdjacentWallCount(int p_x, int p_y) {
        return 42;
    }
}