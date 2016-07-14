/*
 * Object class
 */

// c++ standard libraries
#include <math.h>

// Dragonfly headers
#include "EventJoystick.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "Object.h"
#include "WorldManager.h"

int av::Object::id_iterator = 0;

av::Object::Object() {
    // Generate and set unique object ID
    av::Object::id_iterator++;
    this->id = av::Object::id_iterator;

    this->type = "none";
    this->altitude = 2;

    this->x_velocity = 0;
    this->x_velocity_countdown = 0;
    this->y_velocity = 0;
    this->y_velocity_countdown = 0;

    this->solidness = av::HARD;
    this->no_soft = false;

    this->sprite_index = 0;
    this->sprite_slowdown = 1;
    this->sprite_slowdown_count = 0;

    this->event_count = 0;

    // Add this object to the world
    av::WorldManager &world_manager = av::WorldManager::getInstance();
    world_manager.insertObject(this);
}

av::Object::~Object() {
    av::WorldManager &world_manager = av::WorldManager::getInstance();
    world_manager.removeObject(this);
    
    while (this->event_count > 0) {
        av::LogManager::getInstance().writeLog(0, "av::Object::~Object(): %s", this->event_name[0].c_str());
        this->unregisterInterest(this->event_name[0]);
    }
}

int av::Object::getId() const {
    return this->id;
}

void av::Object::setType(std::string new_type) {
    this->type = new_type;
}

std::string av::Object::getType() const{
    return this->type;
}

int av::Object::setAltitude(int new_alt) {
    if (new_alt < 0 || new_alt > av::MAX_ALTITUDE) {
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog("av::Object::setAltitude(): Altitude outside of range [0, 4], %d", new_alt);
        return -1;
    }
    this->altitude = new_alt;
    return 0;
}

int av::Object::setSolidness(av::Solidness new_solidness) {
    this->solidness = new_solidness;
    return 0;
}

av::Solidness av::Object::getSolidness() const {
    return this->solidness;
}

bool av::Object::causesCollisions() const {
    return (this->solidness == av::HARD) || (this->solidness == av::SOFT);
}

void av::Object::setNoSoft(bool new_no_soft) {
    this->no_soft = new_no_soft;
}

bool av::Object::getNoSoft() const {
    return this->no_soft;
}

double av::Object::getXVelocity() const {
    return this->x_velocity;
}

void av::Object::setXVelocity(float new_x_vel, bool delta) {
    if (delta) {
        this->x_velocity += new_x_vel;
    } else {
        this->x_velocity = new_x_vel;
    }
}

double av::Object::getYVelocity() const {
    return this->y_velocity;
}

void av::Object::setYVelocity(float new_y_vel, bool delta) {
    if (delta) {
        this->y_velocity += new_y_vel;
    } else {
        this->y_velocity = new_y_vel;
    }
}

int av::Object::getXVelocityStep() {
    if (this->x_velocity == 0) {
        return 0;
    }
    this->x_velocity_countdown -= fabs(this->x_velocity);
    if (this->x_velocity_countdown > 0) {
        return 0;
    }
    int spaces = (int) floor(1 - this->x_velocity_countdown);
    this->x_velocity_countdown = 1 + fmod(this->x_velocity_countdown, 1);

    if (this->x_velocity > 0) {
        return spaces;
    } else {
        return -1*spaces;
    }
}

int av::Object::getYVelocityStep() {
    if (this->y_velocity == 0) {
        return 0;
    }
    this->y_velocity_countdown -= fabs(this->y_velocity);
    if (this->y_velocity_countdown > 0) {
        return 0;
    }
    int spaces = (int) floor(1 - this->y_velocity_countdown);
    this->y_velocity_countdown = 1 + fmod(this->y_velocity_countdown, 1);

    if (this->y_velocity > 0) {
        return spaces;
    } else {
        return -1*spaces;
    }
}

int av::Object::getAltitude() const{
    return this->altitude;
}

// virtual function
int av::Object::eventHandler(const av::Event *p_e) {
    return 0;
}

void av::Object::setSpriteIndex(int new_sprite_index) {
    this->sprite_index = new_sprite_index;
}

int av::Object::getSpriteIndex() const {
    return this->sprite_index;
}

void av::Object::setSpriteSlowdown(int new_sprite_slowdown) {
    this->sprite_slowdown = new_sprite_slowdown;
    this->sprite_slowdown_count = new_sprite_slowdown;
}

int av::Object::getSpriteSlowdown() const {
    return this->sprite_slowdown;
}

void av::Object::setSpriteSlowdownCount(int new_sprite_slowdown_count) {
    this->sprite_slowdown_count = new_sprite_slowdown_count;
}

int av::Object::getSpriteSlowdownCount() const {
    return this->sprite_slowdown_count;
}

int av::Object::registerInterest(std::string event_type) {
    if (this->event_count >= av::MAX_OBJ_EVENTS) {
        return -1;
    }

    if (event_type.compare(av::STEP_EVENT) == 0) {
        av::GameManager::getInstance().registerInterest(this, event_type);
    } else if (event_type.compare(av::MOUSE_EVENT) == 0) {
        av::InputManager::getInstance().registerInterest(this, event_type);
    } else if (event_type.compare(av::EVENT_KEYBOARD) == 0) {
        av::InputManager::getInstance().registerInterest(this, event_type);
    } else if (event_type.compare(av::JOYSTICK_EVENT) == 0) {
        av::InputManager::getInstance().registerInterest(this, event_type);
    } else { // Collision, out, and all other events
        av::WorldManager::getInstance().registerInterest(this, event_type);
    }

    this->event_name[this->event_count] = event_type;
    this->event_count++;

    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog("av::Object::registerInterest(): Successfully registered interest for event type %s", event_type.c_str());

    return 0;
}

int av::Object::unregisterInterest(std::string event_type) {
    bool found = false;
    for (int i = 0; i < this->event_count; i++) {
        if (this->event_name[i].compare(event_type) == 0) {
            found = true;
            while (i < this->event_count-1) {
                this->event_name[i] = this->event_name[i+1];
                i++;
            }
            this->event_count--;
        }
    }
    if (!found) {
        return -1;
    }

    if (event_type.compare(av::STEP_EVENT) == 0) {
        av::GameManager::getInstance().unregisterInterest(this, event_type);
    } else if (event_type.compare(av::MOUSE_EVENT) == 0) {
        av::InputManager::getInstance().unregisterInterest(this, event_type);
    } else if (event_type.compare(av::EVENT_KEYBOARD) == 0) {
        av::InputManager::getInstance().unregisterInterest(this, event_type);
    } else if (event_type.compare(av::JOYSTICK_EVENT) == 0) {
        av::InputManager::getInstance().unregisterInterest(this, event_type);
    } else {
        av::WorldManager::getInstance().unregisterInterest(this, event_type);
    }

    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog("av::Object::unregisterInterest(): Successfully unregistered interest for event type %s", event_type.c_str());
    return 0;
}
