/*
 * Music class header
 */

// Dragonfly headers
#include "LogManager.h"
#include "Music.h"

av::Music::Music() {
}

av::Music::~Music() {

}

int av::Music::loadMusic(std::string filename) {
    return 0;
}

void av::Music::setLabel(std::string new_label) {
    this->label = new_label;
}

std::string av::Music::getLabel() const {
    return this->label;
}

void av::Music::play(bool loop) {
}

void av::Music::stop() {
}

void av::Music::pause() {
}
