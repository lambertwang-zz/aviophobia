#pragma once
/*
 * Event Step class header
 *
 * This event is passed to objects on every frame before the update call
 */

#ifndef __EVENT_STEP_H__
#define __EVENT_STEP_H__

// c++ standard libraries
#include <string>

// Dragonfly headers
#include "Event.h"

namespace av {

const std::string STEP_EVENT = "av::step";

    class EventStep : public Event {
    private:
        // Count of game loop iterations
        int step_count;
    public:
        // base constructor
        // Initializes step_count from the GameManager's count
        EventStep();

        // constructor with initial step_count
        EventStep(int init_step_count);
        
        // Sets the step_count
        void setStepCount(int new_step_count);
        // Returns the step_count
        int getStepCount() const;
    };
} // End of namespace

#endif // __EVENT_STEP_H__
