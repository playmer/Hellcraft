// Engine Headers.
#include "Leaf.hpp"

namespace Game {
    Leaf::Leaf(int p_x, int p_y, int p_width, int p_height) :
    m_x { p_x }, m_y { p_y }, m_width { p_width }, m_height { p_height }, 
    m_minLeafSize { 10 }, m_randomBool { 0, 1 }
    {

    }

    bool Leaf::splitLeaf() {
		// Check if this leaf already has two children.
		if (m_childA || m_childB) {
			return false;
		}
		// Determine direction of split, threshold is 25%. Go random elsewise.
		auto f_splitHorizontally = m_randomBool(g_rng);
		if (((double)m_width / (double)m_height) >= 1.25) {
			f_splitHorizontally = false; 
		} else if (((double)m_height / (double)m_width) >= 1.25) {
			f_splitHorizontally = true;
		}

		int f_maxLeafSize;

		if (f_splitHorizontally) {
			f_maxLeafSize = m_height - m_minLeafSize;
		} else {
			f_maxLeafSize = m_width - m_minLeafSize;
		}

		// Too small to split further.
		if (f_maxLeafSize <= m_minLeafSize) {
			return false;
		}

		// Figure out where we want to split leaf.
		std::uniform_int_distribution<int> f_splitter(m_minLeafSize, f_maxLeafSize);
		int f_split = f_splitter(g_rng);

		if (f_splitHorizontally) {
			m_childA = std::make_unique<Leaf>(m_x, m_y, m_width, f_split);
			m_childB = std::make_unique<Leaf>(m_x, m_y + f_split, m_width, m_height - f_split); 
		} else {
			m_childA = std::make_unique<Leaf>(m_x, m_y, f_split, m_height);
			m_childB = std::make_unique<Leaf>(m_x + f_split, m_y, m_width - f_split, m_height); 
		}
		// We successfully split our leaf!
		return true;
	}

    void Leaf::createRooms(std::vector<int>& p_map, BSP& p_bsp) {
		// Search children recursively.
		if (m_childA || m_childB) {
			if (m_childA) {
				m_childA->createRooms(p_map, p_bsp);
			}
			if (m_childB) {
				m_childB->createRooms(p_map, p_bsp);
			}
			if (m_childA && m_childB) {
				p_bsp.createHall(p_map, *m_childA.get()->getRoom(), *m_childB.get()->getRoom());
			}
		} else { // Create rooms in end branches.
			int f_w = std::uniform_int_distribution<int>(p_bsp.getMinRoomSize(), std::min(p_bsp.getMaxRoomSize(), m_width - 1))(g_rng);
			int f_h = std::uniform_int_distribution<int>(p_bsp.getMinRoomSize(), std::min(p_bsp.getMaxRoomSize(), m_height - 1))(g_rng);
			int f_x = std::uniform_int_distribution<int>(m_x, m_x + m_width - 1 - f_w)(g_rng);
			int f_y = std::uniform_int_distribution<int>(m_y, m_y + m_height - 1 - f_h)(g_rng);
			m_room = std::make_unique<Rect>(f_x, f_y, f_w, f_h);
			p_bsp.createRoom(p_map, *m_room);
		}
	}

    std::optional<std::reference_wrapper<Rect>> Leaf::getRoom() {
		// Temp rooms.
		std::optional<std::reference_wrapper<Rect>> f_roomA, f_roomB;
		std::uniform_int_distribution<int> f_roomChoice(0, 1);
		int f_rand = f_roomChoice(g_rng);
		// If we have a room for this leaf node, return it.
		if (m_room) {
			return *m_room;
		} else {
			if (m_childA) {
				f_roomA = m_childA.get()->getRoom();
			}
			if (m_childB) {
				f_roomB = m_childB.get()->getRoom();
			}
			// Neither room.
			if (!m_childA && !m_childB) {
				return std::nullopt;
			} else if (!f_roomB) {
				return f_roomA;
			} else if (!f_roomA) {
				return f_roomB;
			} else if (f_rand) {
				return f_roomA;
			} else {
				return f_roomB;
			}
		}
	}

    Leaf* Leaf::returnChildA() {
        return m_childA ? m_childA.get() : nullptr;
    }

    Leaf* Leaf::returnChildB() {
        return m_childB ? m_childB.get() : nullptr;
    }

    int Leaf::getWidth() {
        return m_width;
    }

    int Leaf::getHeight() {
        return m_height;
    }
}