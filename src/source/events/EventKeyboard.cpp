/*
 * Event Keyboard class
 */

// aviophobia headers
#include "EventKeyboard.h"

av::EventKeyboard::EventKeyboard(SDL_Keycode key, av::EventKeyboardAction action) {
    this->key_code = key;
    this->keyboard_action = action;

    // "av::keyboard"
    this->setType(av::EVENT_KEYBOARD);
}

void av::EventKeyboard::setKey(SDL_Keycode new_key) {
    this->key_code = new_key;

}

SDL_Keycode av::EventKeyboard::getKey() const {
    return this->key_code;
}

void av::EventKeyboard::setAction(av::EventKeyboardAction new_action) {
    this->keyboard_action = new_action;
}

av::EventKeyboardAction av::EventKeyboard::getAction() const {
    return this->keyboard_action;
}
