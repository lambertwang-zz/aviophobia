#pragma once
/*
 * Game manager class header
 *
 * Manages and maintains the game loop
 */

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

// standard headers
#include <functional>

// aviophobia headers
#include "Manager.h"

namespace av {

    // Frame time in microseconds for ~60fps
    const int DEFAULT_FRAME_TIME = 15;

    class GameManager : public Manager {
    private:
        // Singleton
        GameManager();
        // Disallow copy
        GameManager(GameManager const&);
        // Disallow assignment
        void operator=(GameManager const&);

        // Whether or not the game is over
        bool game_over;

        // the target frame time in microseconds of the game loop
        int frame_time;
        // The number of game loops run
        int step_count;

        std::function<void(const av::Event *)> globalEventHandler;

    public:
        // Manages deletion of GameManager
        ~GameManager();

        // Get the instance of the singleton
        static GameManager &getInstance();

        // Starts the GameManager
        int startUp();
        
        // Shut down GameManager
        void shutDown();

        // Virtual function from av::Manager
        bool isValid(std::string event_name) const;
        
        // Runs the game loop
        void run();

        // Sets the game over status
        void setGameOver(bool new_game_over=true);

        // Gets the game over status
        bool getGameOver() const;

        // Returns the frame time
        // Frame time is the target time for the game loop in microseconds
        int getFrameTime() const;

        // Return the step count
        int getStepCount() const;

        // Sets the global event handler callback
        void setGlobalEventHandler(std::function<void(const Event *)> new_global_event_handler);

        // Handles global events
        void handleGlobalEvent(const av::Event *p_event);
    };
} // End of namespace

#endif // __GAME_MANAGER_H__
