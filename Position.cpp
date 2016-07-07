/*
 * Position class
 */

// Dragonfly headers
#include "Position.h"

av::Position::Position(int init_x, int init_y) {
    this->x = init_x;
    this->y = init_y;
}

av::Position::Position() {
    this->x = 0;
    this->y = 0;
}

void av::Position::setX(int new_x) {
    this->x = new_x;
}

int av::Position::getX() const{
    return this->x;
}


void av::Position::setY(int new_y) {
    this->y = new_y;
}

int av::Position::getY() const{
    return this->y;
}

void av::Position::setXY(int new_x, int new_y) {
    this->x = new_x;
    this->y = new_y;
}
