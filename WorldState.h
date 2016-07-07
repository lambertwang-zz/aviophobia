#pragma once
#ifndef __WORLD_STATE_H__
#define __WORLD_STATE_H__

// c++ standard libraries
#include <string>

// aviophobia headers
#include "Manager.h"
#include "Object.h"
#include "Particle.h"
#include "RBTree.h"

namespace av {
    // WorldState
    // Keeps track of object position and orientation
    class WorldState {
    private:
        // List of objects that need to be updated each step
        ObjectList objects;

        RBTree<Object> objects;

        RBTree<Particle> particles;

        // The position that the world view is following
        // When set to NULL, the world will be centered on the origin
        Position* p_viewFollowing;
    public:
        // Constructor
        WorldState();
        // Copy
        WorldState(const WorldState &other);
        // Assignment
        WorldState &operator=(const WorldState &rhs);

        // Returns a list of all objects in the world
        RBTree<Object> getAllObjects(void) const;
    };
} // End of namespace

#endif // __WORLD_STATE_H__
