#pragma once
/*
 * World Manager class header
 *
 * This manager manages the objects in the world
 */

#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__

// c++ standard libraries
#include <string>

// Dragonfly headers
#include "Manager.h"
#include "ObjectList.h"

namespace av {

const int MAX_ALTITUDE = 4;

    class WorldManager : public Manager {
    private:
        // Singleton
        WorldManager();
        // Disallow copy
        WorldManager(WorldManager const&);
        // Disallow assignment
        void operator=(WorldManager const&);

        // List of objects that need to be updated each step
        ObjectList updates;
        // List of objects to be removed from the world
        ObjectList deletions;

        // The object that the view is following
        // Set to NULL for the view to follow an arbitrary position
        av::Object *p_view_following;

    public:
        // Get the instance of the singleton
        static WorldManager &getInstance();

        // Initializes an empty world
        // Returns 0 if successful, -1 otherwise
        int startUp();
        
        // Shut down world manager and delete all of the world's objects
        void shutDown();

        // Virtual function from av::Manager
        bool isValid(std::string event_name) const;

        // Sets the world view centered on some position
        // View edge will not go beyond world boundary
        void setViewPosition(av::Position new_view_pos);

        // Sets the world view to follow some object
        // Set to NULL to stop following
        // If p_new_view_following is not in bounds, return -1 otherwise return 0
        int setViewFollowing(av::Object *p_new_view_following);

        // Adds an object to the world
        // Returns 0 if successfull, -1 otherwise
        int insertObject(Object *p_o);
        // Removes an object from the world
        // Returns 0 if successfull, -1 otherwise
        int removeObject(Object *p_o);

        // Returns a list of all objects in the world
        ObjectList getAllObjects(void) const;

        // Updates the world
        void update();

        // Draws all objects in view bottom up from altitude 0 to MAX_ALTITUDE
        void draw();

        // Indicate Object is to be deleted at the end of the current game loop
        // Returns 0 if successfull, -1 otherwise
        int markForDelete(av::Object *p_o);

        // Returns a list of objects collided with p_o
        // at position where. Considers solid object.
        // Does not care if p_o is solid or not.
        av::ObjectList isCollision(av::Object *p_o, av::Position where);

        // Moves an object
        // If there are no collisions, it moves okay.
        // Returns 0 if the move was ok, -1 if there was a solid collision
        int moveObject(Object *p_o, Position where);
    };
} // End of namespace

#endif // __WORLD_MANAGER_H__
