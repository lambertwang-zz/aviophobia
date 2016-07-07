#pragma once
/*
 * Base manager class header
 *
 * Handles starup and shutdown of managers
 */

#ifndef __MANAGER_H__
#define __MANAGER_H__

// c++ standard libraries
#include <string>

// dragonfly headers
#include "Event.h"
#include "ObjectList.h"

namespace av {

// The maximum number of different events
const int MAX_EVENTS = 128;

    class Manager {
    private:
        // Number of events
        int event_count;
        // List of events
        std::string event[MAX_EVENTS];
        // Objects interested in an event
        av::ObjectList obj_list[MAX_EVENTS];

        // Type identifier
        std::string type;
        // True if manager is started
        bool is_started;
        // Checks to see if the event is handled by this manager
        // Base manager always returns false
        virtual bool isValid(std::string event_name) const;
    protected:
        // Sets the type of the manager
        void setType(std::string type);
    public:
        Manager();
        virtual ~Manager();

        // Returns the type of the manager
        std::string getType() const;

        // Startup Manager
        // Return 0 if successful, negative otherwise
        virtual int startUp();

        // Shutdown Manager
        virtual void shutDown();

        // Return true when startUp() was successful
        bool isStarted() const;

        // Send an event to all objects
        // Return number of objects the event is sent to
        int onEvent(const av::Event *p_event) const;

        // Registers an object as interested in an event
        // Returns 0 if it can register interest, -1 if unsuccessful
        int registerInterest(av::Object *p_o, std::string event_type);

        // Unregisters an object from an event
        // Returns 0 if it can register interest, -1 if unsuccessful
        int unregisterInterest(av::Object *p_o, std::string event_type);
    };
} // End of namespace

#endif // __MANAGER_H__
