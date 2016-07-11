#pragma once
#ifndef __SHAPE_H__
#define __SHAPE_H__

// standard headers
#include <string>

// SDL headers

namespace av {

    class Shape {
    private:
        // Width dimension of the frame
        int width;
        // Height dimension of the frame
        int height;
        // The characters of the frame stored as a string
        std::string frame_str;

        // The renderer program of this shape
        GLuint programId;

        bool shape_initialized;

        // Vertex Attribute location
        GLuint vertexAttribLoc;
        // Vertex buffer object
        GLuint vbo;
        // Index buffer object
        GLuint ibo;
    public:
        // Construct a frame with initial variables
        Shape();
        Shape(int new_width, int new_height, std::string new_frame_str);

        ~Shape();

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

        // Renders the shape.
        // Per frame update (for some reason)
        int update();

        // Renders the shape.
        // Returns [something]
        int render();
    };
} // End of namespace

#endif // __SHAPE_H__