#pragma once
/*
 * Event Keyboard class header
 *
 * This event is passed to objects on key events
 */

#ifndef __EVENT_KEYBOARD_H__
#define __EVENT_KEYBOARD_H__

// standard headers
#include <string>

// SDL headers
#include <SDL_keycode.h>

// aviophobia headers
#include "Event.h"
#include "Input.h"

namespace av {

enum EventKeyboardAction {
    UNDEFINED_KEYBOARD_ACTION = -1,
    KEY_DOWN,
    KEY_UP,
};

const std::string EVENT_KEYBOARD = "av::keyboard";

    class EventKeyboard : public Event {
    private:
        // Key value
        SDL_Keycode key_code;
        // Key action
        av::EventKeyboardAction keyboard_action;
    public:
        // base constructor
        EventKeyboard(SDL_Keycode key, av::EventKeyboardAction action);

        // Sets the key in the event 
        void setKey(SDL_Keycode new_key);
        // Get key from the event
        SDL_Keycode getKey() const;
        // Sets the action in the event
        void setAction(av::EventKeyboardAction new_action);
        // Get action from the event
        av::EventKeyboardAction getAction() const;
    };
} // End of namespace

#endif // __EVENT_KEYBOARD_H__
