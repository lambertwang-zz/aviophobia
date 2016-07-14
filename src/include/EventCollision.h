#pragma once
/*
 * Event Collision class header
 *
 * This event is passed to objects when they collide with eachother
 */

#ifndef __EVENT_COLLISION_H__
#define __EVENT_COLLISION_H__

// c++ standard libraries
#include <string>

// Dragonfly headers
#include "Event.h"
#include "Object.h"

namespace av {

const std::string COLLISION_EVENT = "av::collision";

    class EventCollision : public Event {
    private:
        // The object that caused the collision
        av::Object *p_obj1;
        // The object that was collided with
        av::Object *p_obj2;
    public:
        // base constructor
        // Initializes position at (0, 0) and object1 and 2 as null
        EventCollision();

        // Constructor with initial parameters
        EventCollision(av::Object *p_o1, av::Object *p_o2);
        
        // Sets the object that caused the collision
        void setObject1(av::Object *p_new_o1);
        // Returns the object that caused the collision
        av::Object *getObject1() const;
        // Sets the object that was collided with
        void setObject2(av::Object *p_new_o2);
        // Returns the object that was collided with
        av::Object *getObject2() const;

    };
} // End of namespace

#endif // __EVENT_COLLISION_H__
