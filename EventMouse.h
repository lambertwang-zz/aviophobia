#pragma once
/*
 * Event Mouse class header
 *
 * This event is passed to objects on mouse events
 */

#ifndef __EVENT_MOUSE_H__
#define __EVENT_MOUSE_H__

// c++ standard libraries
#include <string>

// Dragonfly headers
#include "Event.h"
#include "Input.h"

namespace av {

enum EventMouseAction {
    UNDEFINED_MOUSE_ACTION = -1,
    CLICKED,
    PRESSED,
    MOVED,
};

const std::string MOUSE_EVENT = "av::mouse";

    class EventMouse : public Event {
    private:
        // Mouse button
        av::Input::MouseButton mouse_button;
        // Mouse action
        av::EventMouseAction mouse_action;
    public:
        // base constructor
        EventMouse(av::Input::MouseButton button, av::EventMouseAction action);

        // Sets the button in the event 
        void setButton(av::Input::MouseButton new_button);
        // Get button from the event
        av::Input::MouseButton getButton() const;
        // Sets the action in the event
        void setAction(av::EventMouseAction new_action);
        // Get action from the event
        av::EventMouseAction getAction() const;
    };
} // End of namespace

#endif // __EVENT_MOUSE_H__
