/*
 * Base manager class
 */

// dragonfly headers
#include "GameManager.h"
#include "LogManager.h"
#include "Manager.h"
#include "TreeIterator.h"
#include "WorldManager.h"

av::Manager::Manager() {
}

void av::Manager::setType(std::string type) {
    this->type = type;
}

std::string av::Manager::getType() const {
    return this->type;
}

bool av::Manager::isStarted() const {
    return this->is_started;
}

// Definition of virtual functions
av::Manager::~Manager() {
    this->shutDown();
}

int av::Manager::startUp() {
    this->type = "None";
    this->is_started = true;
    this->event_count = 0;
    return 1;
}

void av::Manager::shutDown() {
    this->is_started = false;
}

int av::Manager::onEvent(const av::Event *p_event) const {
    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog(LOG_EVENT, "av::Manager::onEvent(): Sending event \"%s\" to all objects.", p_event->getType().c_str());

    av::GameManager &game_manager = av::GameManager::getInstance();
    game_manager.handleGlobalEvent(p_event);

    int return_count = 0;

    for (int i = 0; i < this->event_count; i++) {
        if (this->event[i].compare(p_event->getType()) == 0) {
            if (this->obj_list[i].isEmpty()) {
                return 0;
            }
            
            av::TreeIterator ti = TreeIterator(&(this->obj_list[i]));

            for (ti.first(); !ti.isDone(); ti.next()) {
                ti.currentObject()->eventHandler(p_event);
                return_count++;
            }
            
            return return_count;
        }
    }
    return 0;
}

int av::Manager::registerInterest(av::Object *p_o, std::string event_type) {

    av::LogManager &log_manager = av::LogManager::getInstance();

    if (!this->isValid(event_type)) {
        log_manager.writeLog(
            "av::Manager::registerInterest(): Object of type %s registering for event type %s is invalid for manager %s",
            p_o->getType().c_str(),
            event_type.c_str(),
            this->getType().c_str()
            );

        return -1;
    }

    log_manager.writeLog(
        LOG_EVENT,
        "av::Manager::registerInterest(): Registering object of type %s with manager %s for event type %s",
        p_o->getType().c_str(),
        this->getType().c_str(),
        event_type.c_str()
        );

    for (int i = 0; i < this->event_count; i++) {
        if (this->event[i].compare(event_type) == 0) {
            this->obj_list[i].insert(p_o);
            return 0;
        }
    }

    if (this->event_count >= av::MAX_EVENTS) {
        return -1;
    }
    this->event[this->event_count] = event_type;
    this->obj_list[this->event_count] = av::ObjectTree();
    this->obj_list[this->event_count].insert(p_o);
    this->event_count++;
    return 0;
}

int av::Manager::unregisterInterest(av::Object *p_o, std::string event_type) {
    for (int i = 0; i < this->event_count; i++) {
        if (this->event[i].compare(event_type) == 0) {
            this->obj_list[i].remove(p_o);
            if (this->obj_list[i].isEmpty()) {
                while (i < this->event_count-1) {
                    this->obj_list[i] = this->obj_list[i+1];
                    i++;
                }
                this->event_count--;
            }
            return 0;
        }
    }

    return -1;
}

bool av::Manager::isValid(std::string event_name) const {
    return false;
}
