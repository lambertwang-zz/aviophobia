#pragma once
#ifndef __SPRITE_H__
#define __SPRITE_H__

// standard headers
#include <string>

// aviophobia headers
#include "Color.h"
#include "Frame.h"

namespace av {

    // const av::Color DEFAULT_SPRITE_COLOR = av::WHITE;

    class Sprite {
    private:
        // Scale of the sprite
        float scale;
        // Number of frames this sprite has
        int frame_count;
        // Array of frames in the sprite
        av::Frame *frames;
        // Label to identify the sprite by
        std::string label;

        // Cannot construct an empty sprite
        Sprite();
    public:
        // Construct a sprite
        Sprite(av::Frame frames);

        // Delete all associated frames on sprite deletion
        ~Sprite();

        // Set the scale of the sprite
        void setScale(int new_scale);
        // Returns the scale of the sprite
        int getScale() const;

        // Set the label of the sprite
        void setLabel(std::string new_label);
        // Returns the label of the sprite
        std::string getLabel() const;

        // Returns the frame count of the sprite
        int getFrameCount() const;

        // Returns a specific frame of the sprite
        // frame_number uses Zero-indexing
        // Returns an empty frame if out of array range
        av::Frame getFrame(int index);
    };
} // End of namespace

#endif // __SPRITE_H__