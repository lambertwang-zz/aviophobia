#pragma once
#ifndef __WORLD_STATE_H__
#define __WORLD_STATE_H__

// c++ standard libraries
#include <string>

// aviophobia headers
#include "Manager.h"
#include "Object.h"
#include "ObjectTree.h"

namespace av {
    // WorldState
    // Keeps track of object position and orientation
    class WorldState {
    private:
        // List of objects in this world state
        ObjectTree objects;

        // Probably needs camera
    public:
        // Constructor
        WorldState();

        WorldState(const ObjectTree *new_objects);
        // Copies an object tree into this state
        void copyObjects(const ObjectTree *new_objects);

        void copy(WorldState new_state);

        ObjectTree *getObjects();
    };
} // End of namespace

#endif // __WORLD_STATE_H__
