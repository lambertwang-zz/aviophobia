#pragma once
/*
 * Object List class header
 *
 * Contains and manages multiple objects
 */

#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

// Dragonfly headers
#include "Object.h"
#include "ObjectListIterator.h"

namespace av {

// Forward reference needed by compiler
class ObjectListIterator;

const int MAX_OBJ_INIT = 4;

    class ObjectList {
    private:
        // The number of objects in the list
        int count;
        // The maximum number of items for the allocated space
        int max_count;
        // List of pointers for dynamically sized array
        av::Object **p_list;

        // Returns the index of where the object with the specified 
        // id is located or where it should be inserted.
        int binSearch(int id) const;
        // Copies another list into this list
        void copyFrom(const av::ObjectList &to_copy);
        // Frees the memory allocated for this list
        void freeList();

    public:
        friend class ObjectListIterator;

        // Constructor for the object list.
        ObjectList();

        // Copy operator
        ObjectList(const av::ObjectList &other);
        // Assignment operator
        ObjectList &operator=(const av::ObjectList &rhs);
        
        // Frees up allocated memory
        ~ObjectList();

        // Insert an object pointer in the list
        // Returns true if successful, false otherwise
        // Maintains order on the list by object id
        // Performs a binary search for insertion sort
        int insert(av::Object *obj);

        // Removes an object pointer from the list
        // Returns 0 if found -1 otherwise
        // Performs a binary search
        int remove(av::Object *obj);

        // Returns true if this list contains the object
        bool contains(av::Object *obj) const;

        // Removes all objects from the list
        void clear();

        // Returns the number of objects in the list
        int getCount() const;

        // Returns the max number of objects
        int getMaxCount() const;

        // Returns whether the list is empty or not
        bool isEmpty() const;

        // Returns whether the list is full or not
        bool isFull() const;

        // Overload + operator for objectLists
        ObjectList operator+(ObjectList list);
    };
} // End of namespace

#endif // __OBJECT_LIST_H__
