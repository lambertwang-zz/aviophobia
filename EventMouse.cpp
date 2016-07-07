/*
 * Event Mouse class
 */

// Dragonfly headers
#include "EventMouse.h"

av::EventMouse::EventMouse(av::Position pos, av::Input::MouseButton button, av::EventMouseAction action) {
    this->mouse_pos = pos;
    this->mouse_button = button;
    this->mouse_action = action;

    // "av::mouse"
    this->setType(av::MOUSE_EVENT);
}

void av::EventMouse::setPos(av::Position new_pos) {
    this->mouse_pos = new_pos;
}

av::Position av::EventMouse::getPos() const {
    return this->mouse_pos;
}    

void av::EventMouse::setButton(av::Input::MouseButton new_button) {
    this->mouse_button = new_button;
}

av::Input::MouseButton av::EventMouse::getButton() const {
    return this->mouse_button;
}

void av::EventMouse::setAction(av::EventMouseAction new_action) {
    this->mouse_action = new_action;
}

av::EventMouseAction av::EventMouse::getAction() const {
    return this->mouse_action;
}
