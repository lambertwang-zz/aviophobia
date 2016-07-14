#pragma once
/*
 * Event class header
 *
 * Events cause things to happen to 
 * objects subscribed to them
 */

#ifndef __EVENT_H__
#define __EVENT_H__

// c++ standard libraries
#include <string>

namespace av {

const std::string UNDEFINED_EVENT = "av::undefined";

    class Event {
    private:
        // A string identifyig the type of event
        std::string event_type;

    public:
        // base Event constructor
        Event();
        
        // Event destructor
        virtual ~Event();

        // Sets the type of the event
        void setType(std::string new_type);
        // Returns the type of the event
        std::string getType() const;
    };
} // End of namespace

#endif // __EVENT_H__


