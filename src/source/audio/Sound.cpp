/*
 * Sound class header
 */

// Dragonfly headers
#include "LogManager.h"
#include "Sound.h"

av::Sound::Sound() {
}

av::Sound::~Sound() {

}

int av::Sound::loadSound(std::string filename) {
    return 0;
}

void av::Sound::setLabel(std::string new_label) {
    this->label = new_label;
}

std::string av::Sound::getLabel() const {
    return this->label;
}

void av::Sound::play(bool) {
}

void av::Sound::stop() {
}

void av::Sound::pause() {
}
