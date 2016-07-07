#pragma once
/*
* Event Quit class header
*
* This event is passed when the window is closed.
*/

#ifndef __EVENT_QUIT_H__
#define __EVENT_QUIT_H__

// c++ standard libraries
#include <string>

// aviophobia headers
#include "Event.h"

namespace av {

    const std::string EVENT_QUIT = "av::quit";

    class EventQuit : public Event {
    private:
    public:
        // base constructor
        // Initializes quit_event
        EventQuit();
    };
} // End of namespace

#endif // __EVENT_QUIT_H__
