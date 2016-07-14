#pragma once
/*
 * Event Joystick class header
 *
 * This event is passed to objects on joystick events
 */

#ifndef __EVENT_JOYSTICK_H__
#define __EVENT_JOYSTICK_H__

// c++ standard libraries
#include <string>

// Dragonfly headers
#include "Event.h"
#include "Input.h"

namespace av {

enum EventJoystickAction {
    UNDEFINED_JOYSTICK_ACTION = -1,
    JOYSTICK_BUTTON_PRESSED,
    JOYSTICK_BUTTON_DOWN,
    AXIS,
};

const std::string JOYSTICK_EVENT = "av::joystick";

    class EventJoystick : public Event {
    private:
        // The id of the joystick event
        unsigned int joystick_id;
        // Axis
        av::Input::Axis axis;
        // axis value
        float axis_value;
        // Button id
        unsigned int button_value;
        // Joystick action
        av::EventJoystickAction joystick_action;
        
    public:
        // Axis constructor
        EventJoystick(unsigned int init_joystick, av::Input::Axis init_axis, float init_axis_value);
        // Button constructor
        EventJoystick(unsigned int init_joystick, av::EventJoystickAction init_action, unsigned int button_value);

        // Returns the id of the joystick
        unsigned int getJoystick() const; 
        // Returns the joystick axis changing
        av::Input::Axis getAxis() const;
        // Returns the joystick axis value
        float getAxisValue() const;
        // Returns the button id changing
        unsigned int getButton() const;
        // Returns the joystick action
        av::EventJoystickAction getAction() const;

    };
} // End of namespace

#endif // __EVENT_JOYSTICK_H__
