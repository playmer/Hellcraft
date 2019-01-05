#pragma once

/*
Signal and slot system which uses std::function and the concept of
connecting and disconnecting a slot from a signal in order to auto-magically
allow emitting of event based data and triggers.
*/

// Standard Headers.
#include <map>
#include <cassert>
#include <iostream>
#include <functional>

namespace Engine {
    // Define the ID of slot as an alias of integer.
    using ID = int;

    // Gives us the next functional ID for a slot, so we can keep track.
    class Generator {
    private:
        ID m_slotId;
    public:
        ID getNext() {
            return m_slotId++;
        };
    };

    // Is the actual signaling library. 
    template <typename... T>
    class Signal {
    public:
        // Define the slot so we don't need yet another class.
        using Slot = std::function<void(T...)>;

        // Various constructors.
        Signal() = default;
        Signal(Signal&&) = default;
        Signal(const Signal&&) = default;

        Signal& operator=(Signal&&) = default;
        Signal& operator=(const Signal&) = default;

        // Send a signal to connected slots.
        void emit(T&&... t) {
            for(auto &s : m_slots) {
                s.second(std::forward<T>(t)...);
            }
        }

        // Register and connect a slot.
        ID connect(Slot p_slot) {
            assert(slot); // Make sure it's not empty.
            return addSlot(std::move(slot));
        }

        // Disconnect a slot.
        void disconnect(ID p_slotID) {
            m_slots.erase(p_slotID);
        }

    private:
        // Register a slot and add it to signal, return it's new ID.
        ID addSlot(Slot&& p_slot) {
            auto f_slotID = generator.getNext();
            m_slots.emplace(f_slotID, std::move(p_slot));
            return f_slotID;
        }

        // Creates new slot IDs.
        Generator generator;
        // Map to hold all slots and signals.
        std::map<ID, Slot> m_slots;
    };
}