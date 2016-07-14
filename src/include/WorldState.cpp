
// aviophobia headers
#include "WorldState.h"

av::WorldState::WorldState() {
    this->objects = NULL;
}

av::WorldState::WorldState(const ObjectTree * new_objects) {
    this->objects = ObjectTree(new_objects);
}

void av::WorldState::copyObjects(const ObjectTree * new_objects) {
    this->objects.copyFrom(new_objects);
}

void av::WorldState::copy(const WorldState new_state) {
    this->copyObjects(&new_state.getObjects());
}


av::ObjectTree av::WorldState::getObjects() const {
    return this->objects;
}
