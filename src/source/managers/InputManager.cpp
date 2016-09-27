/*
 * Input manager class header
 */

// SDL
#include <SDL.h>

// Dragonfly headers
#include "EventJoystick.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventQuit.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"

av::InputManager::InputManager() {

}

av::InputManager::~InputManager() {
    this->shutDown();
}

av::InputManager &av::InputManager::getInstance() {
    static av::InputManager input_manager;
    return input_manager;
}

int av::InputManager::startUp() {
    if (!this->isStarted()) {
        av::Manager::startUp();

        av::LogManager &log_manager = av::LogManager::getInstance();
        
        // Set member parameters
        this->setType("INPUT_MANAGER");

        log_manager.writeLog(2, "av::InputManager::startUp(): InputManager started.");
        return 0;
    }
    return -1;

}

void av::InputManager::shutDown() {
    if (this->isStarted()) {
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog(2, "av::InputManager::shutDown(): Closing InputManager");

        av::Manager::shutDown();
    }
}

void av::InputManager::getInput() {
    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog("av::InputManager::getInput(): Retrieving input.");
    // Get joysticks
    this->joystick_count = 0;

    SDL_LockMutex(av::GraphicsManager::m_eventBuffer);

    int i;
    SDL_Event ev;

    for (i = 0; i < av::GraphicsManager::eventCount; i++) {
        ev = av::GraphicsManager::eventBuffer[i];
        if (ev.type == SDL_QUIT) {
            av::EventQuit e_q = av::EventQuit();
            onEvent(&e_q);
            continue;
        }
        if (ev.type == SDL_KEYDOWN) {
            av::EventKeyboard e_k = av::EventKeyboard(ev.key.keysym.sym, av::KEY_DOWN);
            onEvent(&e_k);
            continue;
        }
        if (ev.type == SDL_KEYUP) {
            av::EventKeyboard e_k = av::EventKeyboard(ev.key.keysym.sym, av::KEY_DOWN);
            onEvent(&e_k);
            continue;
        }
    }

    SDL_UnlockMutex(av::GraphicsManager::m_eventBuffer);
}

bool av::InputManager::isValid(std::string event_name) const {
    if (event_name.compare(av::EVENT_KEYBOARD) == 0) {
        return true;
    }
    if (event_name.compare(av::MOUSE_EVENT) == 0) {
        return true;
    }
    if (event_name.compare(av::JOYSTICK_EVENT) == 0) {
        return true;
    }
    return false;
}

const unsigned int *av::InputManager::getJoysticks() const {
    return this->joysticks;
}

int av::InputManager::getJoystickCount() const {
    return this->joystick_count;
}
