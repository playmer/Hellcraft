#pragma once

/*
Helper class for BSP generation of dungeon tilemap.
*/

// Standard Headers.
#include <tuple>
#include <utility>

namespace Game {
class Rect {
	public:
		Rect(int p_x, int p_y, int p_width, int p_height);
		~Rect();

		bool intersect(Rect& rect);
		std::pair<int, int> getEdge();
		std::pair<int, int> getCenter();
		std::tuple<int, int, int, int> getCorners();

	private:
		int m_x1, m_y1;
		int m_x2, m_y2;
	};
}