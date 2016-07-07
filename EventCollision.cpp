/*
 * Event Collision class
 */

// Dragonfly headers
#include "EventCollision.h"

av::EventCollision::EventCollision() {
    this->pos = av::Position();
    this->p_obj1 = NULL;
    this->p_obj2 = NULL;

    this->setType(av::COLLISION_EVENT);
}

av::EventCollision::EventCollision(av::Object *p_o1, av::Object *p_o2, av::Position p) {
    this->pos = p;
    this->p_obj1 = p_o1;
    this->p_obj2 = p_o2;
    
    this->setType(av::COLLISION_EVENT);
}

void av::EventCollision::setObject1(av::Object *p_new_o1) {
    this->p_obj1 = p_new_o1;
}

av::Object *av::EventCollision::getObject1() const {
    return this->p_obj1;
}

void av::EventCollision::setObject2(av::Object *p_new_o2) {
    this->p_obj2 = p_new_o2;
}

av::Object *av::EventCollision::getObject2() const {
    return this->p_obj2;
}

void av::EventCollision::setPosition(av::Position p) {
    this->pos = p;
}

av::Position av::EventCollision::getPosition() const {
    return this->pos;
}

