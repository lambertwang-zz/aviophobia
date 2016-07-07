#pragma once
#ifndef __GRAPHICS_MANAGER_H__
#define __GRAPHICS_MANAGER_H__

// SDL headers
#include <SDL.h>

// aviophobia headers
#include "Manager.h"
#include "Position.h"

namespace av {

// String justifications.
enum Justification {
    LEFT_JUSTIFIED,
    CENTER_JUSTIFIED,
    RIGHT_JUSTIFIED,
};

// Default settings for window
const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1366;
const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;

const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
const std::string FONT_FILE_DEFAULT = "df-font.ttf";

// Returns the width in pixels of an ascii character
// 32 default
float charHeight(bool default_dimensions = false);
// Returns the height in pixels of an ascii character
// 12.8 default
float charWidth(bool default_dimensions = false);

// Convert ascii spaces (x, y) to pixels (x, y)
av::Position spacesToPixels(av::Position spaces);

// Convert ascii spaces (x, y) to pixels (x, y)
av::Position defaultSpacesToPixels(av::Position spaces);

// Convert pixels (x, y) to ascii spaces (x, y)
av::Position pixelsToSpaces(av::Position pixels);

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
    };
} // End of namespace

#endif // __GRAPHICS_MANAGER_H__
