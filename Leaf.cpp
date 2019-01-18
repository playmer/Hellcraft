// Engine Headers.
#include "Leaf.hpp"

namespace Game {
    Leaf::Leaf(int p_x, int p_y, int p_width, int p_height) :
    m_x { p_x }, m_y { p_y }, m_width { p_width }, m_height { p_height }, m_minLeafSize { 10 },
    m_rng { m_rd() }, m_randomBool { 0, 1 }
    {

    }

    Leaf::~Leaf() {

    }

    bool Leaf::splitLeaf() {
        // Check if this leaf already has two children.
        if(m_childA || m_childB) {
            return false;
        }

        // Determine direction of split, threshold is 25%. Go random elsewise.
        auto f_splitHorizontally = m_randomBool(m_rng);
        if((m_width / m_height) >= 1.25) {
            return false;
        } else if ((m_height / m_width) >= 1.25) {
            return true;
        }

        int f_maxLeafSize;

        if(f_splitHorizontally) {
            f_maxLeafSize = m_height - m_minLeafSize;
        } else  {
            f_maxLeafSize = m_width - m_minLeafSize;
        }

        // Too small to split further.
        if(f_maxLeafSize <= m_minLeafSize) {
            return false;
        }

        // Figure out where we want to split leaf.
        std::uniform_int_distribution<int> f_splitter(m_minLeafSize, f_maxLeafSize);
        int f_split = f_splitter(m_rng);

        if(f_splitHorizontally) {
            m_childA = std::make_unique<Leaf>(m_x, m_y, m_width, f_split);
            m_childB = std::make_unique<Leaf>(m_x, m_y, m_width, m_height - f_split);
        } else {
            m_childA = std::make_unique<Leaf>(m_x, m_y, f_split, m_height);
            m_childB = std::make_unique<Leaf>(m_x, m_y, m_width - f_split, m_height);
        }
    
        // We successfully split our leaf!
        return true;
    }

    std::optional<std::reference_wrapper<Rect>> Leaf::getRoom() {
        // Temp rooms.
        std::optional<std::reference_wrapper<Rect>> f_roomA, f_roomB;
        std::uniform_int_distribution<int> f_roomChoice(0, 1);
        int f_rand = f_roomChoice(m_rng);
        // If we have a room for this leaf node, return it.
        if(m_room) {
            return *m_room;
        } else {
            if(m_childA) {
                f_roomA = m_childA.get()->getRoom();
            }
            if(m_childB) {
                f_roomB = m_childB.get()->getRoom();
            }
            // Neither room.
            if(!m_childA && !m_childB) {
                return std::nullopt;
            } else if(!f_roomB) {
                return f_roomA;
            } else if(!f_roomA) {
                return f_roomB;
            } else if(f_rand) {
                return f_roomA;
            } else {
                return f_roomB;
            }
        }
    }
}