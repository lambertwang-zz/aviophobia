/*
 * Game manager class
 */

// c++ standard libraries
#if defined _WIN32 || defined _WIN64
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#endif

// Dragonfly headers
#include "Clock.h"
#include "EventBeforeDraw.h"
#include "EventStep.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "utility.h"
#include "WorldManager.h"

av::GameManager::GameManager() {
}

av::GameManager &av::GameManager::getInstance() {
    static av::GameManager game_manager;
    return game_manager;
}

// Virtual functions
av::GameManager::~GameManager() {
    this->shutDown();
}

int av::GameManager::startUp() {
    if (!this->isStarted()) {
        av::Manager::startUp();
        // Set member parameters
        this->setType("GAME_MANAGER");
        this->setGameOver(false);

        // 33333 microseconds
        this->frame_time = av::DEFAULT_FRAME_TIME;
        this->step_count = 0;

        // Required for windows
#if defined _WIN32 || defined _WIN64
        timeBeginPeriod(1);
#endif

        // Startup log manager
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.startUp(2);
        log_manager.writeLog(-1, "av::GameManager::startUp(): GameManager started.");

        // Startup graphics manager
        av::GraphicsManager &graphics_manager = av::GraphicsManager::getInstance();
        graphics_manager.startUp();

        // Startup world manager
        av::WorldManager &world_manager = av::WorldManager::getInstance();
        world_manager.startUp();

        // Startup input manager
        av::InputManager  &input_manager = av::InputManager::getInstance();
        input_manager.startUp();

        // Startup resource manager
        av::ResourceManager  &resource_manager = av::ResourceManager::getInstance();
        resource_manager.startUp();

        return 0;
    }
    return -1;
}

void av::GameManager::shutDown() {
    if (this->isStarted()) {
        // Stop game loop
        this->setGameOver(true);

        // Required for windows
#if defined _WIN32 || defined _WIN64
        timeEndPeriod(1);
#endif

        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog(2, "av::GameManager::shutDown(): Closing GameManager");

        // Shutdown managers now
        av::WorldManager &world_manager = av::WorldManager::getInstance();
        world_manager.shutDown();
        av::GraphicsManager &graphics_manager = av::GraphicsManager::getInstance();
        graphics_manager.shutDown();
        av::InputManager  &input_manager = av::InputManager::getInstance();
        input_manager.shutDown();
        av::ResourceManager  &resource_manager = av::ResourceManager::getInstance();
        resource_manager.shutDown();
        log_manager.shutDown();
        av::Manager::shutDown();
    }
}

void av::GameManager::run() {
    if (this->isStarted()) {
        // Create variables required for timing outside of loop scope
        Clock clock;
        int adjust_time = 0;

        av::LogManager &log_manager = av::LogManager::getInstance();

        while (!this->game_over) {

            log_manager.writeLog("av::GameManager::run(): Starting loop step %d", this->step_count);

            // Reset clock
            clock.delta();
            // Increment step count
            this->step_count++;

            // Send EVENT_STEP to all objects
            av::EventStep p_step_event = av::EventStep(this->step_count);
            onEvent(&p_step_event);

            // Retrieve input
            av::InputManager  &input_manager = av::InputManager::getInstance();
            input_manager.getInput();

            av::WorldManager &world_manager = av::WorldManager::getInstance();
            // Call worldManager update
            world_manager.update();

            // Send EVENT_BEFOREDRAW to all objects
            av::EventBeforeDraw p_bd_event = av::EventBeforeDraw();
            onEvent(&p_bd_event);

            // Call worldManager draw
            world_manager.draw();

            // Swap graphics buffers
            av::GraphicsManager &graphics_manager = av::GraphicsManager::getInstance();
            graphics_manager.swapBuffers();

            // Adjust sleep time for additional framerate accuracy
            int loop_time = clock.split();
            long sleep_time = (this->frame_time - loop_time - adjust_time);
            // Reset clock before sleeping to calculate actual sleep time
            clock.delta();
            // Multiply microseconds to obtain sleep time in nanoseconds
            if (sleep_time > 0){
                av::nanoSleep(sleep_time * 1000L);
                // Calculate adjust from difference between expected and actual sleep times
                adjust_time = clock.split() - sleep_time;
            }
            log_manager.writeLog("av::GameManager::run(): Running. Steps: %d, Elapsed (ms): %d, Sleep (ns): %d", this->step_count, loop_time, sleep_time);

        }
    } else {
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog(2, "av::GameManager::run(): GameManager must be started before it can be run");
    }
}

void av::GameManager::setGameOver(bool new_game_over) {
    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog(2, "av::GameManager::setGameOver(): Setting game_over to %s", new_game_over ? "true" : "false");

    this->game_over = new_game_over;
}

bool av::GameManager::getGameOver() const{
    return this->game_over;
}

int av::GameManager::getFrameTime() const{
    return this->frame_time;
}

int av::GameManager::getStepCount() const{
    return this->step_count;
}

void av::GameManager::setGlobalEventHandler(std::function<void(const Event *)> new_global_event_handler) {
    this->globalEventHandler = new_global_event_handler;
}

void av::GameManager::handleGlobalEvent(const av::Event * p_event) {
    this->globalEventHandler(p_event);
}

bool av::GameManager::isValid(std::string event_name) const {
    if (event_name.compare(av::BEFOREDRAW_EVENT) == 0) {
        return true;
    }
    if (event_name.compare(av::STEP_EVENT) == 0) {
        return true;
    }
    return false;
}
