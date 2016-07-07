/*
 * Graphics manager class
 */

// standard headers
#include <string.h>

// SDL headers
#include <SDL.h>

// aviophobia headers
#include "GraphicsManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "utility.h"

// Graphics manger class functions
av::GraphicsManager::GraphicsManager() {

}

av::GraphicsManager &av::GraphicsManager::getInstance() {
    static av::GraphicsManager graphics_manager;
    return graphics_manager;
}

av::GraphicsManager::~GraphicsManager() {
    this->shutDown();
}

int av::GraphicsManager::startUp() {
    return this->startUp(
        av::WINDOW_HORIZONTAL_PIXELS_DEFAULT, 
        av::WINDOW_VERTICAL_PIXELS_DEFAULT,
        false, // Default to windowed mode
        av::WINDOW_TITLE_DEFAULT
    );
}

int av::GraphicsManager::startUp(int new_width, int new_height, bool fullscreen, std::string window_name) {
    if (!this->isStarted()) {
        av::Manager::startUp();

        av::LogManager &log_manager = av::LogManager::getInstance();
        
        // Set member parameters
        this->setType("GRAPHICS_MANAGER");
        this->width = new_width;
        this->height = new_height;

        // Set up sdl context
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            log_manager.writeLog(4, "av::GraphicsManager::startUp(): SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
            return -2;
        }

        //Create window
        Uint32 flags = SDL_WINDOW_SHOWN;
        if (fullscreen) {
            flags ^= SDL_WINDOW_FULLSCREEN;
        }

        this->window = SDL_CreateWindow(
            window_name.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            this->width,
            this->height,
            flags);

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            log_manager.writeLog(4, "av::GraphicsManager::startUp(): SDL could not create window. SDL_Error: %s\n", SDL_GetError());
            return -2;
        }

        // Get window surface
        this->surface = SDL_GetWindowSurface(this->window);

        log_manager.writeLog(2, "av::GraphicsManager::startUp(): GraphicsManager started.");
        return 0;
    }
    return -1;
}

void av::GraphicsManager::shutDown() {
    if (this->isStarted()) {
        av::LogManager &log_manager = av::LogManager::getInstance();

        // End the SDL window
        SDL_DestroyWindow(this->window);

        //Quit SDL subsystems
        SDL_Quit();

        log_manager.writeLog(2, "av::GraphicsManager::shutDown(): Closing GraphicsManager.");
        
        av::Manager::shutDown();
    }
}

int av::GraphicsManager::getWidth() const {
    return this->width;
}

int av::GraphicsManager::getHeight() const {
    return this->height;
}

int av::GraphicsManager::swapBuffers() {
    return 0;
}
