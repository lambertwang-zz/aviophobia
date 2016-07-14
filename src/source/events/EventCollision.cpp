/*
 * Event Collision class
 */

// Dragonfly headers
#include "EventCollision.h"

av::EventCollision::EventCollision() {
    this->p_obj1 = NULL;
    this->p_obj2 = NULL;

    this->setType(av::COLLISION_EVENT);
}

av::EventCollision::EventCollision(av::Object *p_o1, av::Object *p_o2) {
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
