/*
 * Graphics manager class
 */

// standard headers
#include <string.h>

// SDL/GL headers
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <GL/GLU.h>

// aviophobia headers
#include "GameManager.h"
#include "GraphicsManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "Shape.h"
#include "TreeIterator.h"
#include "utility.h"

SDL_Event *av::GraphicsManager::eventBuffer = (SDL_Event *)malloc(sizeof(SDL_Event) * av::EVENT_BUFFER_SIZE);
int av::GraphicsManager::eventCount = 0;
SDL_mutex *av::GraphicsManager::m_eventBuffer = SDL_CreateMutex();

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
        av::DEFAULT_WINDOW_WIDTH, 
        av::DEFAULT_WINDOW_HEIGHT,
        false, // Default to windowed mode
        av::WINDOW_TITLE_DEFAULT
    );
}

int av::GraphicsManager::startUp(int new_width, int new_height, bool new_fullscreen, std::string new_window_name) {
    if (!this->isStarted()) {
        av::Manager::startUp();

        av::LogManager &log_manager = av::LogManager::getInstance();
        
        // Set member parameters
        this->setType("GRAPHICS_MANAGER");
        this->width = new_width;
        this->height = new_height;
        this->fullscreen = new_fullscreen;
        this->window_name = new_window_name;

        log_manager.writeLog(LOG_STARTUP, "av::GraphicsManager::startUp(): GraphicsManager started.");
        return 0;
    }
    return -1;
}

void av::GraphicsManager::shutDown() {
    if (this->isStarted()) {
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog(LOG_STARTUP, "av::GraphicsManager::shutDown(): Closing GraphicsManager.");
        
        av::Manager::shutDown();
    }
}

int av::GraphicsManager::getWidth() const {
    return this->width;
}

int av::GraphicsManager::getHeight() const {
    return this->height;
}

int av::GraphicsManager::renderLoop(void *data) {
    av::GameManager &game_manager = av::GameManager::getInstance();
    av::GraphicsManager &graphics_manager = av::GraphicsManager::getInstance();
    graphics_manager.setupRendering();

    while (!game_manager.getGameOver()) {
        SDL_LockMutex(av::GameManager::m_render_state);
        SDL_CondWait(av::GameManager::c_render_state, av::GameManager::m_render_state);

        // Call worldManager draw
        graphics_manager.draw();

        graphics_manager.pollEvents();

        // Swap graphics buffers
        graphics_manager.swapBuffers();

        SDL_UnlockMutex(av::GameManager::m_render_state);
    }

    graphics_manager.teardownRendering();

    return 0;
}

int av::GraphicsManager::setupRendering() {
    av::LogManager &log_manager = av::LogManager::getInstance();
    if (!this->isStarted()) {
        log_manager.writeLog("av::GraphicsManager::setupRendering(): Manager must be started before rendering can begin.");
    }

    // Set up sdl context
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_manager.writeLog("av::GraphicsManager::setupRendering(): SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
        return -2;
    }

    // Set OpenGL 3.1 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Create window
    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    if (fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    this->window = SDL_CreateWindow(
        window_name.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        this->width,
        this->height,
        flags);

    // Enable text input
    SDL_StartTextInput();

    // Create GL context
    this->context = SDL_GL_CreateContext(this->window);

    if (this->context == NULL) {
        log_manager.writeLog("av::GraphicsManager::setupRendering(): SDL could not create GL context. SDL_Error: %s\n", SDL_GetError());
        return -2;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        log_manager.writeLog("av::GraphicsManager::setupRendering(): Unable to initialize GLEW. GLEW Error: %s\n", glewGetErrorString(glewError));
        return -2;
    }

    // Enable Vsync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        log_manager.writeLog("av::GraphicsManager::setupRendering(): Unable to set VSync. SDL Error: %s\n", SDL_GetError());
        return -2;
    }
    
    // Get window surface
    this->surface = SDL_GetWindowSurface(this->window);

    log_manager.writeLog(LOG_STARTUP, "av::GraphicsManager::setupRendering(): Rendering context set up.");
    return 0;
}

void av::GraphicsManager::teardownRendering() {
    // End the SDL window
    SDL_DestroyWindow(this->window);

    //Quit SDL subsystems
    SDL_Quit();
}

void av::GraphicsManager::pollEvents() {
    SDL_LockMutex(av::GraphicsManager::m_eventBuffer);
    av::GraphicsManager::eventCount = 0;
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        av::GraphicsManager::eventBuffer[av::GraphicsManager::eventCount] = ev;
        av::GraphicsManager::eventCount++;
    }
    SDL_UnlockMutex(av::GraphicsManager::m_eventBuffer);
}

void av::GraphicsManager::draw() {
    TreeIterator ti = TreeIterator(av::GameManager::render_state.getObjects());
    for (ti.first(); !ti.isDone(); ti.next()) {
        av::Object *p_o = ti.currentObject();
        // TODO: Only draw objects in view
    }
}

int av::GraphicsManager::swapBuffers() {
    // Shape temp = Shape();
    // temp.render();

    SDL_GL_SwapWindow(this->window);
    return 0;
}

void av::GraphicsManager::drawTriangle() {
}

void av::GraphicsManager::drawQuad() {

}