#pragma once
#ifndef __FRAME_H__
#define __FRAME_H__

// standard headers
#include <string>

// aviophobia headers
#include "shape.h"

namespace av {

    class Frame {
    private:
        // Width dimension of the frame
        int width;
        // Height dimension of the frame
        int height;
        // The characters of the frame stored as a string
        std::string frame_str;
    public:
        // Construct a frame with initial variables
        Frame(int new_width = 0, int new_height = 0, std::string new_frame_str = "");

        // Set the width of the frame
        void setWidth(int new_width);
        // Returns the width of the frame
        int getWidth() const;

        // Set the height of the frame
        void setHeight(int new_height);
        // Returns the height of the frame
        int getHeight() const;

        // Set the frame string of the frame
        void setString(std::string new_frame_str);
        // Returns the frame string of the frame
        std::string getString() const;
    };
} // End of namespace

#endif // __FRAME_H__