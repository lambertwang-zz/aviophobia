/*
 * Resource Manager class
 */

// c++ standard libraries
#include <string>
#include <string.h>

// Dragonfly headers
#include "LogManager.h"
#include "ResourceManager.h"

av::ResourceManager::ResourceManager() {
    this->startUp();
}

av::ResourceManager &av::ResourceManager::getInstance() {

    static av::ResourceManager resource_manager;
    return resource_manager;
}

int av::ResourceManager::startUp() {
    if (!this->isStarted()) {
        av::Manager::startUp();

        // Set member variables and initialize lists
        this->setType("RESOURCE_MANAGER");
        
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog(2, "av::ResourceManager::startUp(): Starting ResourceManager");

        return 0;
    }
    return -1;
}

void av::ResourceManager::shutDown() {
    if (this->isStarted()) {
        // Frees all sprites
        
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog(2, "av::ResourceManager::shutDown(): Closing ResourceManager");

        av::Manager::shutDown();
    }
}

int av::ResourceManager::loadSprite(std::string filename, std::string label) {
    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog(
        2, 
        "av::ResourceManager::loadSprite(): Loading sprite from file '%s' into label '%s'", 
        filename.c_str(), 
        label.c_str()
        );

    std::ifstream spritefile(filename.c_str());

    if (spritefile.is_open()) {
        // Read header information
        int frames = av::extractTagInt(&spritefile, av::FRAMES_TOKEN.c_str());
        int width = av::extractTagInt(&spritefile, av::WIDTH_TOKEN.c_str());
        int height = av::extractTagInt(&spritefile, av::HEIGHT_TOKEN.c_str());
        std::string color = av::extractTagString(&spritefile, av::COLOR_TOKEN.c_str());
        
        if (spritefile.good()) {
            std::string line;
            getline(spritefile, line);
            if (line.compare(av::END_SPRITE_TOKEN) != 0) {
                log_manager.writeLog(
                    2, 
                    "av::loadSprite(): Error incorrect END_SPRITE_TOKEN, expected '%s' found '%s' in file '%s'", 
                    av::END_SPRITE_TOKEN.c_str(), 
                    line.c_str(),
                    filename.c_str()
                    );
            }
        } else {
            log_manager.writeLog(
                2, 
                "av::loadSprite(): Error END_SPRITE_TOKEN '%s' not found in file '%s'", 
                av::END_SPRITE_TOKEN.c_str(),
                filename.c_str()
                );
        }

        spritefile.close();

        return 0;
    } else { // unable to open file
        log_manager.writeLog(
            2, 
            "av::ResourceManager::loadSprite(): Error opening file '%s'", 
            filename.c_str()
            );
        return -1;
    }
}

int av::ResourceManager::unloadSprite(std::string label) {
    int i = 0;
    return -1;
}

int av::extractTagInt(std::ifstream *p_file, const char *tag) {
    std::string line;
    if (p_file->good()) {
        getline(*p_file, line);
    }
    if (line.compare(0, strlen(tag), tag) == 0) {
        return atoi(line.substr(strlen(tag)+1).c_str());
    } else {
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog(2, "av::extractTagInt(): Error expected tag '%s' on line '%s'", 
            tag,
            line.c_str());
        return -1;
    }
}

std::string av::extractTagString(std::ifstream *p_file, const char *tag) {
    std::string line;
    if (p_file->good()) {
        getline(*p_file, line);
    }
    if (line.compare(0, strlen(tag), tag) == 0) {
        return line.substr(strlen(tag)+1).c_str();
    } else {
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog(2, "av::extractTagString(): Error expected tag '%s' on line '%s'", 
            tag,
            line.c_str());
        return "";
    }
}

int av::ResourceManager::loadSound(std::string filename, std::string label) {
    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog(
        2, 
        "av::ResourceManager::loadSound(): Loading sound from file '%s' into label '%s'", 
        filename.c_str(), 
        label.c_str()
        );

    if (this->sound_count >= av::MAX_SOUNDS) {
        log_manager.writeLog(
            2, 
            "av::ResourceManager::loadSound(): Sound limit reached, sound '%s' not loaded", 
            label.c_str()
            );
        return -1;
    }

    av::Sound *new_sound = new av::Sound();
    new_sound->setLabel(label);
    if (new_sound->loadSound(filename) == -1) {
        return -1;
    } else {
        this->p_sounds[this->sound_count] = new_sound;
        this->sound_count++;
        return 0;
    }
}

int av::ResourceManager::unloadSound(std::string label) {
    int i = 0;
    while (i < this->sound_count) {
        if (label.compare(this->p_sounds[i]->getLabel()) == 0) {
            // No actual method for freeing sounds
            for (i; i < this->sound_count-1; i++) {
                this->p_sounds[i] = this->p_sounds[i+1];
            }
            this->sound_count--;
            av::LogManager &log_manager = av::LogManager::getInstance();
            log_manager.writeLog(
                2, 
                "av::ResourceManager::unloadSound(): Sound with label '%s' unloaded", 
                label.c_str()
                );
            return 0;
        }
        i++;
    }
    return -1;
}

av::Sound *av::ResourceManager::getSound(std::string label) const {
    for (int i = 0; i < this->sound_count; i++) {
        if (label.compare(this->p_sounds[i]->getLabel()) == 0) {
            return this->p_sounds[i];
        }
    }
    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog(2, "av::ResourceManager::getSound(): Sound with label '%s' not found", label.c_str());
    return NULL;
}

int av::ResourceManager::loadMusic(std::string filename, std::string label) {
    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog(
        2, 
        "av::ResourceManager::loadMusic(): Loading music from file '%s' into label '%s'", 
        filename.c_str(), 
        label.c_str()
        );

    if (this->music_count >= av::MAX_MUSIC) {
        log_manager.writeLog(
            2, 
            "av::ResourceManager::loadMusic(): Music limit reached, music '%s' not loaded", 
            label.c_str()
            );
        return -1;
    }

    av::Music *new_music = new av::Music();
    new_music->setLabel(label);
    if (new_music->loadMusic(filename) == -1) {
        return -1;
    } else {
        this->p_music[this->music_count] = new_music;
        this->music_count++;
        return 0;
    }
}

int av::ResourceManager::unloadMusic(std::string label) {
    int i = 0;
    while (i < this->music_count) {
        if (label.compare(this->p_music[i]->getLabel()) == 0) {
            // No actual method for freeing music
            this->p_music[i]->setLabel("");
            av::LogManager &log_manager = av::LogManager::getInstance();
            log_manager.writeLog(
                2, 
                "av::ResourceManager::unloadMusic(): Music with label '%s' unloaded", 
                label.c_str()
                );
            return 0;
        }
        i++;
    }
    return -1;
}

av::Music *av::ResourceManager::getMusic(std::string label) const {
    for (int i = 0; i < this->music_count; i++) {
        if (label.compare(this->p_music[i]->getLabel()) == 0) {
            return this->p_music[i];
        }
    }
    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog(2, "av::ResourceManager::getMusic(): Music with label '%s' not found", label.c_str());
    return NULL;
}
