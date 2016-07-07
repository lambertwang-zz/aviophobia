/*
 * World Manager class
 */

// Dragonfly headers
#include "EventBeforeDraw.h"
#include "EventCollision.h"
#include "EventJoystick.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ObjectListIterator.h"
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
        this->updates = av::ObjectList();
        this->deletions = av::ObjectList();

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
        av::ObjectList all_obj = this->updates;
        
        av::ObjectListIterator li(&all_obj);

        while (!this->updates.isEmpty()) {

            li.first();
            while(!li.isDone()) {
                av::Object *p_o = li.currentObject();
                // log_manager.writeLog(0, "av::WorldManager::shutDown(): Deleting object of type");
                log_manager.writeLog(0, "av::WorldManager::shutDown(): Deleting object of type %s", p_o->getType().c_str());
                delete p_o;
                li.next();
            }
        }

        log_manager.writeLog(2, "av::WorldManager::shutDown(): Closing WorldManager");

        av::Manager::shutDown();
    }
}

void av::WorldManager::setViewPosition(av::Position new_view_pos) {
    av::GraphicsManager &graphics_manager = av::GraphicsManager::getInstance();

    av::Position temp_pos = av::Position(new_view_pos.getX(), new_view_pos.getY());
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


av::ObjectList av::WorldManager::getAllObjects(void) const {
    return this->updates;
}


void av::WorldManager::update() {
    // Calculate movement
    av::ObjectListIterator move_i(&this->updates);
    for (move_i.first(); !move_i.isDone(); move_i.next()) {
        av::Object *p_o = move_i.currentObject();
        int x = p_o->getXVelocityStep();
        int y = p_o->getYVelocityStep();

        if (x != 0 || y != 0) {
            av::Position last_pos = p_o->getPos();
            av::Position new_pos(last_pos.getX()+x, last_pos.getY()+y);
            this->moveObject(p_o, new_pos);
        }
    }

    // Check if deletions is not empty
    if (!this->deletions.isEmpty()) {
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog(0, "av::WorldManager::update(): Removing %d objects from the world", this->deletions.getCount());
        
        av::ObjectListIterator li(&this->deletions);
        for (li.first(); !li.isDone(); li.next()) {
            this->removeObject(li.currentObject());
            delete li.currentObject();
        }
        this->deletions.clear();
    }
}

void av::WorldManager::draw() {
    // Iterate through the object list 5 times, once for each altitude layer
    av::ObjectListIterator li(&this->updates);
    for (int i = 0; i <= MAX_ALTITUDE; i++) {
        for (li.first(); !li.isDone(); li.next()) {
            av::Object *p_o = li.currentObject();
            // Only draw objects in view
        }
    }
}

int av::WorldManager::markForDelete(av::Object *p_o) {
    // ObjectList::insert will not add duplicate objects
    this->updates.remove(p_o);
    return this->deletions.insert(p_o);
}

av::ObjectList av::WorldManager::isCollision(av::Object *p_o, av::Position where) {
    // Create an objectlist for return
    av::ObjectList collision_list;

    av::ObjectListIterator li(&this->updates);

    for (li.first(); !li.isDone(); li.next()) {
        av::Object *p_temp_o = li.currentObject();

        // Ignore self
        if (p_temp_o != p_o) {
        }
    }
    return collision_list;
}

int av::WorldManager::moveObject(av::Object *p_o, av::Position where) {
    av::Position previous = *(new av::Position(p_o->getPos().getX(), p_o->getPos().getY()));
    // Set position to new position
    // Will be reverted if movement is obstructed
    p_o->setPos(where);

    // Calculate collisions
    if (p_o->causesCollisions()) {
        av::ObjectList collidedObjects = this->isCollision(p_o, where);

        if (!collidedObjects.isEmpty()) {
            bool can_move = true;

            av::ObjectListIterator li(&collidedObjects);
            for (li.first(); !li.isDone(); li.next()) {
                av::Object *p_temp_o = li.currentObject();

                // Create a collision event
                av::EventCollision collision(p_o, p_temp_o, where);

                av::LogManager &log_manager = av::LogManager::getInstance();
                log_manager.writeLog(1, "av::WorldManager::moveObject(): Sending collision event, object id %d collided with object id %d", 
                    p_o->getId(), p_temp_o->getId());

                p_o->eventHandler(&collision);
                p_temp_o->eventHandler(&collision);

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
                p_o->setPos(previous);
                return -1;
            }
        } // No collision
    }
    // If world view following this object, move world view position
    if (this->p_view_following == p_o) {
        setViewPosition(p_o->getPos());
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
    if (event_name.compare(av::BEFOREDRAW_EVENT) == 0) {
        return false;
    }
    return true;
}
