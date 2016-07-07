#pragma once
/*
 * Resource Manager class header
 *
 * This manager manages the game's resources including sprites and sounds
 */

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

// c++ standard libraries
#include <fstream>
#include <string>

// Dragonfly headers
#include "Manager.h"
#include "Music.h"
#include "Sound.h"

namespace av {

// Maximum number of unique sprites in the game
const int MAX_SPRITES = 1024;
// Maximum number of unique sounds in the game
const int MAX_SOUNDS = 128;
// Maximum number of unique music in the game
const int MAX_MUSIC = 128;

// Sprite text file format syntax
const std::string FRAMES_TOKEN = "frames";
const std::string WIDTH_TOKEN = "width";
const std::string HEIGHT_TOKEN = "height";
const std::string COLOR_TOKEN = "color";
const std::string END_FRAME_TOKEN = "end";
const std::string END_SPRITE_TOKEN = "eof";

    class ResourceManager : public Manager {
    private:
        // Singleton
        ResourceManager();
        // Disallow copy
        ResourceManager(ResourceManager const&);
        // Disallow assignment
        void operator=(ResourceManager const&);

        // Array of all sounds in the game
        av::Sound *p_sounds[MAX_SPRITES];
        // Count of number of loaded sounds
        int sound_count;

        // Array of all music in the game
        av::Music *p_music[MAX_SPRITES];
        // Count of number of loaded music
        int music_count;

    public:
        // Get the instance of the singleton
        static ResourceManager &getInstance();

        // Prepares the manager for loading resources
        // Returns 0 if successful, -1 otherwise
        int startUp();
        
        // Shut down resource manager
        // frees all of the resources allocated
        void shutDown();

        // Loads a sprite from a file
        // Returns 0 if successful, -1 otherwise
        int loadSprite(std::string filename, std::string label);

        // Unloads a sprite with the indicated label
        // Returns 0 if successful, -1 otherwise
        int unloadSprite(std::string label);

        // Loads a sound from a file
        // Returns 0 if successful, -1 otherwise
        int loadSound(std::string filename, std::string label);

        // Unloads a sound with the indicated label
        // Returns 0 if successful, -1 otherwise
        int unloadSound(std::string label);

        // Finds a sound with the indicated label.
        // Returns a pointer if found otherwise NULL
        av::Sound *getSound(std::string label) const;

        // Loads music from a file
        // Returns 0 if successful, -1 otherwise
        int loadMusic(std::string filename, std::string label);

        // Unloads music with the indicated label
        // Returns 0 if successful, -1 otherwise
        int unloadMusic(std::string label);

        // Finds music with the indicated label.
        // Returns a pointer if found otherwise NULL
        av::Music *getMusic(std::string label) const;
    };

    // Helper functions for reading sprite files
    // Read a line with a tag and a number and returns the number
    int extractTagInt(std::ifstream *p_file, const char *tag);
    // Read a line with a tag and a string and returns the string
    std::string extractTagString(std::ifstream *p_file, const char *tag);
    
} // End of namespace

#endif // __RESOURCE_MANAGER_H__
