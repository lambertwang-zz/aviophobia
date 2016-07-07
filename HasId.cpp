
// aviophobia headers
#include "HasId.h"

int av::HasId::id_iterator = 0;

av::HasId::HasId() {
    // Generate and set unique object ID
    av::HasId::id_iterator++;
    this->id = av::HasId::id_iterator;
}

int av::HasId::getId() const {
    return this->id;
}