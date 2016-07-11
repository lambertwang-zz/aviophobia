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
#include "GraphicsManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "Shape.h"
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
        av::DEFAULT_WINDOW_WIDTH, 
        av::DEFAULT_WINDOW_HEIGHT,
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

        // Create GL context
        this->context = SDL_GL_CreateContext(this->window);

        if (this->context == NULL) {
            log_manager.writeLog(4, "av::GraphicsManager::startUp(): SDL could not create GL context. SDL_Error: %s\n", SDL_GetError());
            return -2;
        }

        // Initialize GLEW
        glewExperimental = GL_TRUE;
        GLenum glewError = glewInit();
        if (glewError != GLEW_OK) {
            log_manager.writeLog(4, "av::GraphicsManager::startUp(): Unable to initialize GLEW. GLEW Error: %s\n", glewGetErrorString(glewError));
            return -2;
        }

        // Enable Vsync
        if (SDL_GL_SetSwapInterval(1) < 0) {
            log_manager.writeLog(4, "av::GraphicsManager::startUp(): Unable to set VSync. SDL Error: %s\n", SDL_GetError());
            return -2;
        }
    /*
    void printProgramLog(GLuint program) {
        //Make sure name is shader
        if (glIsProgram(program)) {
            //Program log length
            int infoLogLength = 0;
            int maxLength = infoLogLength;

            //Get info string length
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            //Allocate string
            char* infoLog = new char[maxLength];

            //Get info log
            glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
            if (infoLogLength > 0) {
                //Print Log
                printf("%s\n", infoLog);
            }

            //Deallocate string
            delete[] infoLog;
        } else {
            printf("Name %d is not a program\n", program);
        }
    }

    void printShaderLog(GLuint shader) {
        //Make sure name is shader
        if (glIsShader(shader)) {
            //Shader log length
            int infoLogLength = 0;
            int maxLength = infoLogLength;

            //Get info string length
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            //Allocate string
            char* infoLog = new char[maxLength];

            //Get info log
            glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
            if (infoLogLength > 0) {
                //Print Log
                printf("%s\n", infoLog);
            }

            //Deallocate string
            delete[] infoLog;
        } else {
            printf("Name %d is not a shader\n", shader);
        }
    }*/

    ////////////////////////////////////////
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
    Shape temp = Shape();
    temp.render();
    SDL_GL_SwapWindow(this->window);
    return 0;
}

void av::GraphicsManager::drawTriangle() {
}

void av::GraphicsManager::drawQuad() {

}