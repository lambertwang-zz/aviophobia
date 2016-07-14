/*
 * Event class
 */

// Dragonfly headers
#include "Event.h"

// Create a generic undefined event
av::Event::Event() {
    this->event_type = av::UNDEFINED_EVENT;
}
        
av::Event::~Event() {
}

void av::Event::setType(std::string new_type) {
    this->event_type = new_type;
}

std::string av::Event::getType() const {
    return this->event_type;
}
