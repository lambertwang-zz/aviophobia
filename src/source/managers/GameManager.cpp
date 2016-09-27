/*
 * Game manager class
 */

// standard headers
#if defined _WIN32 || defined _WIN64
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#endif

// aviophobia headers
#include "Clock.h"
#include "EventStep.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "utility.h"
#include "WorldManager.h"


#include "Shape.h"

av::WorldState av::GameManager::game_state = WorldState();
av::WorldState av::GameManager::render_state = WorldState();
SDL_mutex *av::GameManager::m_game_state = SDL_CreateMutex();
SDL_mutex *av::GameManager::m_render_state = SDL_CreateMutex();
SDL_cond *av::GameManager::c_game_state = SDL_CreateCond();
SDL_cond *av::GameManager::c_render_state = SDL_CreateCond();

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

        this->frame_time = av::DEFAULT_FRAME_TIME;
        this->step_count = 0;

        // Set default global event handler to null
        this->setGlobalEventHandler(&(this->defaultGlobalEventHandler));

        // Required for windows
#if defined _WIN32 || defined _WIN64
        timeBeginPeriod(1);
#endif

        // Startup log manager
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.startUp(2);
        log_manager.writeLog(LOG_STARTUP, "av::GameManager::startUp(): GameManager started.");

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
        log_manager.writeLog(LOG_STARTUP, "av::GameManager::shutDown(): Closing GameManager");

        // Shutdown managers now
        av::GraphicsManager &graphics_manager = av::GraphicsManager::getInstance();
        graphics_manager.shutDown();
        av::WorldManager &world_manager = av::WorldManager::getInstance();
        world_manager.shutDown();
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
        // Create a thread for moving world state buffers
        SDL_Thread* swapStateThreadId = SDL_CreateThread(
            &av::GameManager::swapStates,
            "SwapStateThread",
            NULL);
            

        // Put rendering on a different thread
        SDL_Thread* renderingThreadId = SDL_CreateThread(
            &av::GraphicsManager::renderLoop, 
            "RenderingThread", 
            NULL);    
        
        this->gameLoop();

        SDL_WaitThread(renderingThreadId, NULL);
        SDL_WaitThread(swapStateThreadId, NULL);
    } else {
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog("av::GameManager::run(): GameManager must be started before it can be run");
    }
}

int av::GameManager::swapStates(void *data) {
    WorldState swapState = WorldState();

    av::GameManager &game_manager = av::GameManager::getInstance();

    while (!game_manager.getGameOver()) {
        // Always wait for a gamestate update
        SDL_LockMutex(m_game_state);
        SDL_CondWait(c_game_state, m_game_state);

        // Swap the game state into itself
        swapState.copy(game_state);

        SDL_UnlockMutex(m_game_state);

        // Lock the render state
        SDL_LockMutex(m_render_state);
        
        render_state.copy(swapState);

        SDL_UnlockMutex(m_render_state);
        SDL_CondSignal(c_render_state);
    }

    return 0;
}

void av::GameManager::gameLoop() {
    // Create variables required for timing outside of loop scope
    Clock clock;
    int adjust_time = 0;

    av::LogManager &log_manager = av::LogManager::getInstance();
    av::InputManager  &input_manager = av::InputManager::getInstance();
    av::WorldManager &world_manager = av::WorldManager::getInstance();

    while (!this->game_over) {
        // Reset clock
        clock.delta();

        log_manager.writeLog(LOG_GAME_TICK, "av::GameManager::gameLoop(): Starting loop step %d", this->step_count);

        // Increment step count
        this->step_count++;

        // Lock the game state
        SDL_LockMutex(m_game_state);

        // Send EVENT_STEP to all objects
        av::EventStep p_step_event = av::EventStep(this->step_count);
        onEvent(&p_step_event);

        // Retrieve input
        input_manager.getInput();

        // Call worldManager update
        world_manager.update();

        // Unlock the mutex
        SDL_UnlockMutex(m_game_state);
        SDL_CondSignal(c_game_state);

        // Adjust sleep time for additional framerate accuracy
        int loop_time = clock.delta();
        // Reset clock before sleeping to calculate actual sleep time
        // clock.delta();
        long sleep_time = (this->frame_time - loop_time - adjust_time);
        // Multiply microseconds to obtain sleep time in nanoseconds
        if (sleep_time > 0){
            av::microSleep(sleep_time);
            // Calculate adjust from difference between expected and actual sleep times
            adjust_time = clock.split() - sleep_time;
        } else {
            adjust_time = 0;
        }
        log_manager.writeLog(
            LOG_GAME_TICK,
            "av::GameManager::gameLoop(): Running. Steps: %d, Elapsed (us): %d, Sleep (us): %d, Adjust (us): %d", 
            this->step_count, loop_time, sleep_time, adjust_time);
    }
}

void av::GameManager::setGameOver(bool new_game_over) {
    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog("av::GameManager::setGameOver(): Setting game_over to %s", new_game_over ? "true" : "false");

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
    if (event_name.compare(av::STEP_EVENT) == 0) {
        return true;
    }
    return false;
}

void av::GameManager::defaultGlobalEventHandler(const av::Event *p_event) {
    return;
}
