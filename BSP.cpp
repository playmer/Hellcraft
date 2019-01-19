// Game Headers.
#include "BSP.hpp"

namespace Game {
    BSP::BSP() : m_maxLeafSize { 24 }, m_minRoomSize { 6 }, m_maxRoomSize { 15 },
    m_smoothingFactor { 1 }, m_fillingFactor { 3 }, m_smoothEdges { true }
    {

    }

    BSP::~BSP() {

    }

    void BSP::generateLevel(std::vector<int>& p_map, int p_mapWidth, int p_mapHeight) {
		// Create empty 1D "2D" vector that we'll end up assigning the p_map to.
		m_mapWidth = p_mapWidth;
		m_mapHeight = p_mapHeight;
		m_bspMap.resize(p_mapWidth * p_mapHeight, Tiles::Empty);

		std::unique_ptr<Leaf> f_rootLeaf = std::make_unique<Leaf>(0, 0, p_mapWidth, p_mapHeight);

		// Create a vector of leaves.
		std::vector<Leaf*> f_leaves;
		f_leaves.emplace_back(f_rootLeaf.get());

        // Used in splitting.
		std::uniform_int_distribution<int> f_dist(0, 10);

		// Keep looping until nothing can be split anymore.
		while (f_leaves.size() > 0) {
			auto l_leaf = f_leaves.back();
			f_leaves.pop_back();   
			if (l_leaf->getWidth() > m_maxLeafSize || l_leaf->getHeight() > m_maxLeafSize || f_dist(g_rng) > 8) {
				if (l_leaf->splitLeaf()) {
					auto f_splitA = l_leaf->returnChildA();
					f_leaves.emplace_back(f_splitA);
					auto f_splitB = l_leaf->returnChildB();
					f_leaves.emplace_back(f_splitB);
				}
			}
		}

		// Create rooms.
		f_rootLeaf->createRooms(*this);

		// Cleanup map.
		cleanUpMap(m_mapWidth, m_mapHeight);

		// Done. Assign our BSP map to the actual tileset map that was passed in and be done with it.   
		p_map = m_bspMap;
	}

    void BSP::createRoom(Rect& p_room) {
        for(int l_x = (std::get<0>(p_room.getCorners()) + 1); l_x < std::get<2>(p_room.getCorners()); ++l_x) {
            for(int l_y = (std::get<1>(p_room.getCorners()) + 1); l_y < std::get<3>(p_room.getCorners()); ++l_y) {
                m_bspMap[m_mapWidth * l_y + l_x] = Tiles::Floor;
            }
        }
    }

    void BSP::createHall(Rect& p_roomA, Rect& p_roomB) {
        auto f_walker = p_roomB.getCenter();
        auto f_goal = p_roomA.getCenter();
        while ((f_goal.first <= f_walker.first && f_walker.first <= f_goal.first) && (f_goal.second < f_walker.second && f_walker.second < f_goal.second)) {
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
                if(m_bspMap[m_mapWidth * f_walker.second + f_walker.first] == Tiles::Floor){
                    m_bspMap[m_mapWidth * f_walker.second + f_walker.first] = Tiles::Empty;
                }
            }
        }
    }
    
    void BSP::cleanUpMap(int p_mapWidth, int p_mapHeight) {
        if(m_smoothEdges) {
            for(int l_i = 0; l_i < 3; l_i++) {
                for(int l_x = 1; l_x < m_mapWidth - 1; l_x++) {
                    for(int l_y = 1; l_y < m_mapHeight - 1; l_y++) {
                        if(m_bspMap[p_mapWidth * l_y + l_x] == Tiles::Floor && getAdjacentWallCount(l_x, l_y) <= m_smoothingFactor){
                            m_bspMap[p_mapWidth * l_y + l_x] = Tiles::Empty;
                        }
                        if(m_bspMap[p_mapWidth * l_y + l_x] == Tiles::Empty && getAdjacentWallCount(l_x, l_y) >= m_fillingFactor){
                            m_bspMap[p_mapWidth * l_y + l_x] = Tiles::Floor;
                        }
                    }
                }
            }
        }
    }

    int BSP::getAdjacentWallCount(int p_x, int p_y) {
        int f_wallCounter = 0;
        if(m_bspMap[m_mapWidth * (p_y - 1) +  p_x] == Tiles::Floor) {
            f_wallCounter++;
        } 
        if(m_bspMap[m_mapWidth * (p_y + 1) + p_x ] == Tiles::Floor) {
            f_wallCounter++;
        } 
        if(m_bspMap[m_mapWidth * p_y + (p_x - 1)] == Tiles::Floor) {
            f_wallCounter++;
        }
        if(m_bspMap[m_mapWidth * p_y + (p_x + 1)] == Tiles::Floor) {
            f_wallCounter++;
        }
        return f_wallCounter;
    }

    int BSP::getMinRoomSize() {
        return m_minRoomSize;
    }

    int BSP::getMaxRoomSize() {
        return m_maxRoomSize;
    }
}