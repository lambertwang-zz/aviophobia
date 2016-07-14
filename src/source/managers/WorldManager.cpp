/*
 * World Manager class
 */

// aviophobia headers
#include "EventCollision.h"
#include "EventJoystick.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ObjectTree.h"
#include "TreeIterator.h"
#include "utility.h"
#include "WorldManager.h"

av::WorldManager::WorldManager() {
    this->startUp();
}

av::WorldManager &av::WorldManager::getInstance() {
    static av::WorldManager world_manager;
    return world_manager;
}

int av::WorldManager::startUp() {
    if (!this->isStarted()) {
        av::Manager::startUp();

        // Set member variables and initialize lists
        this->setType("WORLD_MANAGER");
        this->updates = av::ObjectTree();
        this->deletions = av::ObjectTree();

        av::GraphicsManager &graphics_manager = av::GraphicsManager::getInstance();
        this->p_view_following = NULL;

        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog(2, "av::WorldManager::startUp(): Starting WorldManager");

        return 0;
    }
    return -1;
}

void av::WorldManager::shutDown() {
    if (this->isStarted()) {
        av::LogManager &log_manager = av::LogManager::getInstance();
        // Delete all game objects
        av::ObjectTree all_obj = this->updates;
        
        av::TreeIterator ti(&all_obj);

        while (!this->updates.isEmpty()) {

            ti.first();
            while(!ti.isDone()) {
                av::Object *p_o = ti.currentObject();
                // log_manager.writeLog(0, "av::WorldManager::shutDown(): Deleting object of type");
                log_manager.writeLog(0, "av::WorldManager::shutDown(): Deleting object of type %s", p_o->getType().c_str());
                delete p_o;
                ti.next();
            }
        }

        log_manager.writeLog(2, "av::WorldManager::shutDown(): Closing WorldManager");

        av::Manager::shutDown();
    }
}

int av::WorldManager::setViewFollowing(av::Object *p_new_view_following) {
    this->p_view_following = p_new_view_following;
    return 1;
}

int av::WorldManager::insertObject(Object *p_o) {
    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog(0, "av::WorldManager::insertObject(): Adding object to world id: %d", p_o->getId());

    return this->updates.insert(p_o);
}

int av::WorldManager::removeObject(Object *p_o) {
    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog(0, "av::WorldManager::removeObject(): Removing object of type %s from world id: %d", p_o->getType().c_str(), p_o->getId());

    // Check if removing the view followed object
    if (p_o == this->p_view_following) {
        this->p_view_following = NULL;
    }

    return this->updates.remove(p_o);
}


av::ObjectTree av::WorldManager::getAllObjects(void) const {
    return this->updates;
}


void av::WorldManager::update() {
    // Calculate movement
    av::TreeIterator move_i(&this->updates);
    for (move_i.first(); !move_i.isDone(); move_i.next()) {
        av::Object *p_o = move_i.currentObject();
        int x = p_o->getXVelocityStep();
        int y = p_o->getYVelocityStep();

        if (x != 0 || y != 0) {
        }
    }

    // Check if deletions is not empty
    if (!this->deletions.isEmpty()) {
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog(0, "av::WorldManager::update(): Removing %d objects from the world", this->deletions.getCount());
        
        av::TreeIterator li(&this->deletions);
        for (li.first(); !li.isDone(); li.next()) {
            this->removeObject(li.currentObject());
            delete li.currentObject();
        }
        this->deletions.clear();
    }
}

int av::WorldManager::markForDelete(av::Object *p_o) {
    // ObjectList::insert will not add duplicate objects
    this->updates.remove(p_o);
    return this->deletions.insert(p_o);
}

av::ObjectTree av::WorldManager::isCollision(av::Object *p_o) {
    // Create an objectlist for return
    av::ObjectTree collision_list;

    av::TreeIterator li(&this->updates);

    for (li.first(); !li.isDone(); li.next()) {
        av::Object *p_temp_o = li.currentObject();

        // Ignore self
        if (p_temp_o != p_o) {
        }
    }
    return collision_list;
}

int av::WorldManager::moveObject(av::Object *p_o) {
    // Calculate collisions
    if (p_o->causesCollisions()) {
        av::ObjectTree collidedObjects = this->isCollision(p_o);

        if (!collidedObjects.isEmpty()) {
            bool can_move = true;

            av::TreeIterator li(&collidedObjects);
            for (li.first(); !li.isDone(); li.next()) {
                av::Object *p_temp_o = li.currentObject();

                // Create a collision event
                // av::EventCollision collision(p_o, p_temp_o);

                av::LogManager &log_manager = av::LogManager::getInstance();
                log_manager.writeLog(1, "av::WorldManager::moveObject(): Sending collision event, object id %d collided with object id %d", 
                    p_o->getId(), p_temp_o->getId());

                // p_o->eventHandler(&collision);
                // p_temp_o->eventHandler(&collision);

                // If Both objects are hard and this object is not stopped by soft objects
                // Then movement is obstructed
                if (
                    ((p_o->getSolidness() == av::HARD) && 
                        (p_temp_o->getSolidness() == av::HARD)) || 
                    ((p_o->getNoSoft()) && 
                        (p_temp_o->getSolidness() == av::SOFT))
                    ) {
                    can_move = false;
                }
            }
            // If cannot move, return -1
            if (!can_move) {
                // Rollback position
                return -1;
            }
        } // No collision
    }
    // If world view following this object, move world view position
    if (this->p_view_following == p_o) {
    }

    return 0;
}

bool av::WorldManager::isValid(std::string event_name) const {
    if (event_name.compare(av::STEP_EVENT) == 0) {
        return false;
    }
    if (event_name.compare(av::EVENT_KEYBOARD) == 0) {
        return false;
    }
    if (event_name.compare(av::MOUSE_EVENT) == 0) {
        return false;
    }
    if (event_name.compare(av::JOYSTICK_EVENT) == 0) {
        return false;
    }
    return true;
}
