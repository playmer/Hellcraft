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
		p_map.resize(p_mapWidth * p_mapHeight, Tiles::Empty);

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
					f_leaves.emplace_back(l_leaf->returnChildA());
					f_leaves.emplace_back(l_leaf->returnChildB());
				}
			}
		}

		// Create rooms.
		f_rootLeaf->createRooms(p_map, *this);

		// Cleanup map and we're done.
		cleanUpMap(p_map, m_mapWidth, m_mapHeight);
	}

    void BSP::createRoom(std::vector<int>& p_map, Rect& p_room) {
        for(int l_x = (std::get<0>(p_room.getCorners()) + 1); l_x < std::get<2>(p_room.getCorners()); ++l_x) {
            for(int l_y = (std::get<1>(p_room.getCorners()) + 1); l_y < std::get<3>(p_room.getCorners()); ++l_y) {
                p_map[m_mapWidth * l_y + l_x] = Tiles::Floor;
            }
        }
    }

    void BSP::createHall(std::vector<int>& p_map, Rect& p_roomA, Rect& p_roomB) {
        auto f_walker = p_roomB.getCenter();
        auto f_goal = p_roomA.getCenter();
        auto f_goalEdges = p_roomA.getEdge();
        while (!((f_goal.first <= f_walker.first && f_walker.first <= f_goalEdges.first) && (f_goal.second < f_walker.second && f_walker.second < f_goalEdges.second))) {
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
                if(p_map[m_mapWidth * f_walker.second + f_walker.first] == Tiles::Floor){
                    p_map[m_mapWidth * f_walker.second + f_walker.first] = Tiles::Empty;
                }
            }
        }
    }
    
    void BSP::cleanUpMap(std::vector<int>& p_map, int p_mapWidth, int p_mapHeight) {
        if(m_smoothEdges) {
            for(int l_i = 0; l_i < 3; l_i++) {
                for(int l_x = 1; l_x < m_mapWidth - 1; l_x++) {
                    for(int l_y = 1; l_y < m_mapHeight - 1; l_y++) {
                        if(p_map[p_mapWidth * l_y + l_x] == Tiles::Floor && getAdjacentWallCount(p_map, l_x, l_y) <= m_smoothingFactor){
                            p_map[p_mapWidth * l_y + l_x] = Tiles::Empty;
                        }
                        if(p_map[p_mapWidth * l_y + l_x] == Tiles::Empty && getAdjacentWallCount(p_map, l_x, l_y) >= m_fillingFactor){
                            p_map[p_mapWidth * l_y + l_x] = Tiles::Floor;
                        }
                    }
                }
            }
        }
    }

    int BSP::getAdjacentWallCount(std::vector<int>& p_map, int p_x, int p_y) {
        int f_wallCounter = 0;
        if(p_map[m_mapWidth * (p_y - 1) +  p_x] == Tiles::Floor) {
            f_wallCounter++;
        } 
        if(p_map[m_mapWidth * (p_y + 1) + p_x] == Tiles::Floor) {
            f_wallCounter++;
        } 
        if(p_map[m_mapWidth * p_y + (p_x - 1)] == Tiles::Floor) {
            f_wallCounter++;
        }
        if(p_map[m_mapWidth * p_y + (p_x + 1)] == Tiles::Floor) {
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