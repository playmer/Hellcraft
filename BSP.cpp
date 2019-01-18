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
                            f_leaves.emplace_back(std::move(l_leaf.returnChildA().value().get()));
                            f_leaves.emplace_back(std::move(l_leaf.returnChildB().value().get()));
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
        auto f_walker = p_roomB.getCenter();
        auto f_goal = p_roomA.getCenter();
        while ((f_goal.first <= f_walker.first && f_walker.first <= room1.first) && (room1.second < f_walker.second && f_walker.second < room1.second)) {
            // Directions.
            double f_n = 1.0, f_s = 1.0, f_e = 1.0, f_w = 1.0;
            double f_weightFactor = 1.0;
            if(f_walker.first < f_goal.first) {
                f_e += f_weightFactor;
            } else if(f_walker.first > f_goal.first) {
                f_w += f_weightFactor;
            }
            if(f_walker.second < f_goal.second) {
                f_s += f_weightFactor;
            } else if(f_walker.second > f_goal.second) {
                f_n += f_weightFactor;
            }
            // Normalize probablities.
            double f_total = f_e + f_w + f_n + f_s;
            f_n /= f_total;
            f_e /= f_total;
            f_w /= f_total;
            f_s /= f_total;

            // Choose direction.
            int f_dx, f_dy;
            std::uniform_real_distribution<double> f_choice(0, 1);
            auto f_dir = f_choice(g_rng);
            if(0 <= f_dir && f_dir < f_n) {
                f_dx = 0;
                f_dy = -1;
            } else if(f_n <= f_dir && f_dir < (f_n + f_s)) {
                f_dx = 0;
                f_dy = 1;
            } else if((f_n + f_s) <= f_dir && f_dir < (f_n + f_e + f_s)) {
                f_dx = 1;
                f_dy = 0;
            } else {
                f_dx = -1;
                f_dy = 0;
            }
            // Walk & check edge collision. 
            if((0 < (f_walker.first + f_dx) && (f_walker.first + f_dx) < m_mapWidth - 1) && 
               (0 < (f_walker.second + f_dy) && (f_walker.second + f_dy) < m_mapHeight - 1)) {
                f_walker.first += f_dx;
                f_walker.second += f_dy;
                if(m_bspMap[m_mapWidth * f_walker.first + f_walker.second] == Tiles::Floor){
                    m_bspMap[m_mapWidth * f_walker.first + f_walker.second] = Tiles::Empty;
                }
            }
        }
    }
    
    void BSP::cleanUpMap(int p_mapWidth, int p_mapHeight) {

    }

    int BSP::getAdjacentWallCount(int p_x, int p_y) {
        return 42;
    }
}