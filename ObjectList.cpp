/*
 * Object List class
 */

// c++ standard libraries
#include <stdlib.h>
#include <cstring>
#include <stdio.h>

// Dragonfly headers
#include "ObjectList.h"
#include "LogManager.h"

av::ObjectList::ObjectList() {
    this->count = 0;
    this->max_count = av::MAX_OBJ_INIT;

    this->p_list = (av::Object **) malloc(sizeof(av::Object *) * max_count);
}

av::ObjectList::ObjectList(const av::ObjectList &other) {
    this->copyFrom(other);
}

av::ObjectList& av::ObjectList::operator=(const av::ObjectList &rhs) {
    // Make sure objects aren't the same
    if (this != &rhs) {
        // Free current list if allocated already
        this->freeList();

        this->copyFrom(rhs);
    }
    return *this;
}

av::ObjectList::~ObjectList() {
    this->freeList();
}

// freeList, copyFrom helper methods defined to avoid duplicate code
void av::ObjectList::copyFrom(const av::ObjectList &to_copy) {
    // Allocate space for this list and copy list over
    this->p_list = (av::Object **) malloc(sizeof(av::Object *) * to_copy.getMaxCount());
    memcpy(this->p_list, to_copy.p_list, sizeof(av::Object *) * to_copy.getMaxCount());

    // Set member variables
    this->max_count = to_copy.getMaxCount();
    this->count = to_copy.getCount();
}

void av::ObjectList::freeList() {
    // If this list is already allocated
    if (this->p_list) {
        // Free memory
        av::LogManager &log_manager = av::LogManager::getInstance();
        log_manager.writeLog(-1, "av::ObjectList::~ObjectList(): Freeing memory at %p", this->p_list);

        free(this->p_list);
    }
}

int av::ObjectList::binSearch(int id) const {
    // Binary search

    // Search range
    int m = 0;
    int n = count;

    // Search head
    int search = 0;

    while (n-m > 0) {
        // retrieve middle element of range 
        // AKA: floor((m+n)/2)
        search = (m+n) >> 1;
        
        // If element found, break
        if (id == this->p_list[search]->getId()) {
            m = search;
            break;
        } if (this->p_list[search]->getId() > id) {
            n = search;
        } else {
            m = search+1;
        }
    }

    return m;
}

int av::ObjectList::insert(av::Object *obj) {
    av::LogManager &log_manager = av::LogManager::getInstance();
    
    int object_index = this->binSearch(obj->getId());
    // Check if object already exists in list
    if (this->count > object_index) {
        if (this->p_list[object_index]->getId() == obj->getId()) {
            return -1;
        }
    }

    // Check if space exists in list
    if (this->count == this->max_count) {
        this->max_count *= 2;
        log_manager.writeLog(1, "av::ObjectList::insert(): Object list allocating additional memory for %d objects", this->max_count);

        // Reallocate list to a larger space
        av::Object **p_temp_list;
        p_temp_list = (av::Object **) realloc(this->p_list, sizeof(av::Object *) * this->max_count);
        this->p_list = p_temp_list;
    }

    log_manager.writeLog(-1, "av::ObjectList::insert(): Inserting object at index %d", object_index);

    // Shift all objects past the desired index up
    for (int i = this->count; i > object_index; i--) {
        this->p_list[i] = this->p_list[i-1];
        log_manager.writeLog(-2, "av::ObjectList::insert(): Accessing indices %d and %d", i, i-1);
    }
    
    this->p_list[object_index] = obj;
    this->count++;

    log_manager.writeLog(-1, "av::ObjectList::insert(): Object with id %d successfully inserted at index %d", this->p_list[object_index]->getId(), object_index);
    
    return 0;
}

int av::ObjectList::remove(av::Object *obj) {
    av::LogManager &log_manager = av::LogManager::getInstance();
    int object_index = this->binSearch(obj->getId());

    // Check if object exists
    if (object_index >= this->count) {
        return -1;
    }
    if (this->p_list[object_index]->getId() != obj->getId()) {
        return -1;
    }

    log_manager.writeLog(-1, "av::ObjectList::remove(): removing object at index %d", object_index);

    // Shift all objects past the desired index down
    for (int i = object_index; i < this->count-1; i++) {
        this->p_list[i] = this->p_list[i+1];
        log_manager.writeLog(-2, "av::ObjectList::remove(): Accessing indices %d and %d", i, i+1);
    }

    this->count--;

    log_manager.writeLog(-1, "av::ObjectList::remove(): Object with id %d successfully removed from index %d", this->p_list[object_index]->getId(), object_index);
    return 0;
}

bool av::ObjectList::contains(av::Object *obj) const {
    if (this->isEmpty()) {
        return false;
    }
    int object_index = this->binSearch(obj->getId());

    // Check if object exists
    if (object_index >= this->count) {
        return false;
    }
    return this->p_list[object_index]->getId() == obj->getId();
}

void av::ObjectList::clear() {
    // Set count to 0.
    this->count = 0;

    av::LogManager &log_manager = av::LogManager::getInstance();
    log_manager.writeLog(0, "av::ObjectList::clear(): Object list cleared");
}

int av::ObjectList::getCount() const {
    return this->count;
}

int av::ObjectList::getMaxCount() const {
    return this->max_count;
}

bool av::ObjectList::isEmpty() const {
    return this->count == 0;
}

bool av::ObjectList::isFull() const {
    return this->count == this->max_count;
}

// Allow joining of lists through the + operator
av::ObjectList av::ObjectList::operator+(av::ObjectList list_to_add) {
    // Copy list to return list
    av::ObjectList return_list = av::ObjectList(*this);

    av::ObjectListIterator li(&list_to_add);

    // Add elements of lists together
    for (li.first(); !li.isDone(); li.next()) {
        av::Object *p_o = li.currentObject();
        return_list.insert(p_o);
    }

    return return_list;
}
