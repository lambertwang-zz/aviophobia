#pragma once
/*
 * Object List Iterator class header
 *
 * Iterates through an object list
 */

#ifndef __OBJECT_LIST_ITERATOR_H__
#define __OBJECT_LIST_ITERATOR_H__

// Dragonfly headers
#include "Object.h"
#include "ObjectList.h"

namespace av {

// Forward reference needed by compiler
class ObjectList;

    class ObjectListIterator {
    private:
        // Iterator must be given list when created
        ObjectListIterator();
        // Index into the list
        int index;
        // Pointer to the object list iterated on
        const ObjectList *p_list;

    public:
        // Creates an iterator for a specific object_list
        ObjectListIterator(const ObjectList *p_obj_list);

        // Puts the index to the start of the list
        void first();
        // Increments the index by one
        void next();
        // Returns whether or not the index is at the end of the list
        bool isDone() const;
        
        // Returns the object currently at the 
        av::Object *currentObject() const;
    };
} // End of namespace

#endif // __OBJECT_ITERATOR_LIST_H__
