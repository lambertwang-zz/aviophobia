#pragma once
#ifndef __GRAPHICS_MANAGER_H__
#define __GRAPHICS_MANAGER_H__

// SDL headers
#include <SDL.h>

// aviophobia headers
#include "Manager.h"

namespace av {

// Default settings for window
const int DEFAULT_WINDOW_WIDTH = 800;
const int DEFAULT_WINDOW_HEIGHT = 600;

const std::string WINDOW_TITLE_DEFAULT = "aviophobia";
    /**
    *   GraphicsManager
    *   Handles creation of a window and rendering to the window.
    **/
    class GraphicsManager : public Manager {
    private:
        // Pointer to the SDL window
        SDL_Window *window;
        // The surface containing the window
        SDL_Surface *surface;

        // The OpenGL Context
        SDL_GLContext context;

        // Singleton
        GraphicsManager();
        // Disallow copy
        GraphicsManager(GraphicsManager const&);
        // Disallow assignment
        void operator=(GraphicsManager const&);

        // Width of the window in pixels
        int width;
        // Height of the window in pixels
        int height;
    public:
        // Manages deletion of GraphicsManager
        ~GraphicsManager();

        // Get the instance of the singleton
        static GraphicsManager &getInstance();

        // Starts the GraphicsManager with default parameters
        int startUp();
        // Starts the GraphicsManager
        int startUp(
            int init_horizontal, 
            int init_vertical, 
            bool fullscreen,
            std::string window_name
        );

        // Shut down GraphicsManager
        void shutDown();

        // Returns the width of the window in pixels
        int getWidth() const;
        // Returns the height of the window in pixels
        int getHeight() const;

        // Render the current window buffer
        // Returns 0 if successful, -1 otherwise
        int swapBuffers();

        // Renders a triangle
        void drawTriangle();

        // Renders a quad
        void drawQuad();
    };
} // End of namespace

#endif // __GRAPHICS_MANAGER_H__
