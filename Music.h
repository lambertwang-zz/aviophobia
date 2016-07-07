#pragma once
/*
 * Music class header
 *
 * For background music and longer pieces of audio
 */

#ifndef __MUSIC_H__
#define __MUSIC_H__

// SFML Includes
#include <SDL.h>

// c++ standard libraries
#include <string>

// aviophobia headers
#include "HasId.h"

namespace av {

    class Music: public HasId {
    private:
        // Disallow copy
        Music (av::Music const&);
        // Disallow assignment
        void operator=(av::Music const&);

        // The unique label of the music
        std::string label;

    public:
        // The music constructor
        Music();
        // The music destructor
        ~Music();

        // Associate a music buffer with a file
        // Returns -1 if failed, 0 if successful
        int loadMusic(std::string filename);

        // Set the label of the music
        void setLabel(std::string new_label);
        // Returns the label of the music
        std::string getLabel() const;

        // Plays the music, possible endlessely
        void play(bool loop = false);
        // Stops the music
        void stop();
        // Pauses the music
        void pause();
    };
} // End of namespace

#endif // __MUSIC_H__
