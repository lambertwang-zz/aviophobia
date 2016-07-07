/*
 * Event Joystick class
 */

// Dragonfly headers
#include "EventJoystick.h"

av::EventJoystick::EventJoystick(unsigned int init_joystick, av::Input::Axis init_axis, float init_axis_value) {
    this->joystick_id = init_joystick;
    this->axis = init_axis;
    this->axis_value = init_axis_value;
    this->button_value = 0;
    this->joystick_action = av::AXIS;
    // "av::joystick"
    this->setType(av::JOYSTICK_EVENT);
}

av::EventJoystick::EventJoystick(unsigned int init_joystick, av::EventJoystickAction init_action, unsigned int button_value) {
    this->joystick_id = init_joystick;
    this->axis = av::Input::UNDEFINED_AXIS;
    this->axis_value = 0;
    this->button_value = button_value;
    this->joystick_action = init_action;
    // "av::joystick"
    this->setType(av::JOYSTICK_EVENT);
}

unsigned int av::EventJoystick::getJoystick() const {
    return this->joystick_id;
}

av::Input::Axis av::EventJoystick::getAxis() const {
    return this->axis;
}

float av::EventJoystick::getAxisValue() const {
    return this->axis_value;
}

unsigned int av::EventJoystick::getButton() const {
    return this->button_value;
}

av::EventJoystickAction av::EventJoystick::getAction() const {
    return this->joystick_action;
}
