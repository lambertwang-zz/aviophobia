#pragma once
/*
 * Sound class header
 *
 * For basic sound effects
 */

#ifndef __SOUND_H__
#define __SOUND_H__

// SDL
#include <SDL.h>

// c++ standard libraries
#include <string>

// aviophobia headers
#include "Object.h"

namespace av {

    class Sound: public Object {
    private:
        // The unique label of the sound
        std::string label;

    public:
        // The sound constructor
        Sound();
        // The sound destructor
        ~Sound();

        // Load a sound buffer from a file
        // Returns -1 if failed, 0 if successful
        int loadSound(std::string filename);

        // Set the label of the sound
        void setLabel(std::string new_label);
        // Returns the label of the sound
        std::string getLabel() const;

        // Plays the sound, possible endlessely
        void play(bool loop = false);
        // Stops the sound
        void stop();
        // Pauses the sound
        void pause();
    };
} // End of namespace

#endif // __SOUND_H__
