#pragma once
/*
 * Input manager class header
 *
 * Manages user unput and input events
 */

#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

// Dragonfly headers
#include "Manager.h"

namespace av {

    class InputManager : public Manager {
    private:
        // Singleton
        InputManager();
        // Disallow copy
        InputManager(InputManager const&);
        // Disallow assignment
        void operator=(InputManager const&);

        // The number of joysticks
        int joystick_count;
        // The ids of the joysticks
        // Up to 4 joysticks are supported
        unsigned int joysticks[4];

    public:
        // Manages deletion of InputManager
        ~InputManager();

        // Get the instance of the singleton
        static InputManager &getInstance();

        // Starts the InputManager
        int startUp();
        
        // Shut down InputManager
        void shutDown();

        // Virtual function from av::Manager
        bool isValid(std::string event_name) const;
        
        // Gets input from the keyboard and mouse
        void getInput();

        // Returns an array of joysticks
        const unsigned int *getJoysticks() const;
        // Returns the count of joysticks
        int getJoystickCount() const;

    };
} // End of namespace

#endif // __INPUT_MANAGER_H__
