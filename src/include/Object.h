#pragma once
/*
 * Object class header
 *
 * Objects that exist in the game and do things
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

// c++ standard libraries
#include <string>

// aviophobia headers
#include "Event.h"

namespace av {

enum Solidness {
    HARD,       // Causes collisions and obstructs movement
    SOFT,       // Causes collisions but allows movement
    SPECTRAL,   // Neither causes collisions nor obstructs movements
};

const int MAX_OBJ_EVENTS = 128;

    class Object {
    private:
        // The unique object identifier
        // The id is not allowed to be set. Setting it can and will screw
        // with insertion and removal from ObjectLists because they store
        // Objects ordered by id.
        int id;
        // For maintaining a unique id for each object
        static int id_iterator;

        // The user-defined type for the object
        std::string type;
        
        // Defines the drawing order of the object. 0 gets drawn first and MAX_ALTITUDE gets drawn last
        int altitude;
        // The object's solidness
        av::Solidness solidness;
        // Whether to allow movement onto a soft object
        // True if this object won't move into soft objects
        bool no_soft;

        // Horizontal velocity
        double x_velocity;
        // Countdown for horizontal movement
        double x_velocity_countdown;
        // Vertical velocity
        double y_velocity;
        // Countdown for vertical movement
        double y_velocity_countdown;

        // The current sprite frame
        int sprite_index;
        // The number of frames each frame is drawn for
        // If 0, the sprite is frozen
        int sprite_slowdown;
        // The number of frames until the sprite frame changes
        int sprite_slowdown_count;


        // Number of events the object is registered for
        int event_count;
        // List of events the object is registered for
        std::string event_name[av::MAX_OBJ_EVENTS];

    public:
        // Constructor for the object.
        // Sets its parameters to default
        // Adds itself to the world
        Object();

        // Manages deletion of the object
        // Removes the object from the game world
        virtual ~Object();

        // Gets the object's id
        int getId() const;

        // Sets the object's type
        void setType(std::string new_type);
        // Gets the object's type
        std::string getType() const;

        // Sets the object's altitude
        // If new_alt is not within the acceptable range, return -1
        // otherwise, return 0
        int setAltitude(int new_alt);
        // Returns the object's altitude
        int getAltitude() const;

        // Sets the object's solidness
        int setSolidness(av::Solidness new_solidness);
        // Gets the object's solidness
        av::Solidness getSolidness() const;
        // Returns whether or not this object causes collisions
        bool causesCollisions() const;

        // Sets the no_soft status of this object
        void setNoSoft(bool new_no_soft = true);
        // Returns the no_soft status of this object
        bool getNoSoft() const;

        // get x velocity
        double getXVelocity() const;
        // set x velocity
        void setXVelocity(float new_x_vel, bool delta = false);
        // get y velocity
        double getYVelocity() const;
        // set y velocity
        void setYVelocity(float new_y_vel, bool delta = false);

        // Performs 1 step of horizontal movement
        // Return the horizontal movement amount
        int getXVelocityStep();

        // Performs 1 step of vertical movement
        // Return the vertical movement amount
        int getYVelocityStep();

        // Sets the index of the current sprite
        void setSpriteIndex(int new_sprite_index);
        // Returns the index of the current sprite
        int getSpriteIndex() const;

        // Slows down sprite animations
        void setSpriteSlowdown(int new_sprite_slowdown);
        // Returns the sprite slowdown
        int getSpriteSlowdown() const;

        // Sets the sprite's current slowdown count
        void setSpriteSlowdownCount(int new_sprite_slowdown_count);
        // Returns the sprite's current slowdown count
        int getSpriteSlowdownCount() const;

        // Defined behavior for the object when certain events are passed to it
        // Returns 0 if event is ignored, otherwise 1
        virtual int eventHandler(const av::Event *p_e);

        // Register the object for interest in an event
        // Keeps track of the manager and the event
        // Returns 0 if successful -1 otherwise
        int registerInterest(std::string event_type);

        // Unregister the object's interest in an event
        // Returns 0 if successful -1 otherwise
        int unregisterInterest(std::string event_type);
    };
} // End of namespace

#endif // __OBJECT_H__
