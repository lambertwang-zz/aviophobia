#pragma once
#ifndef __TREEITERATOR_H__
#define __TREEITERATOR_H__

// aviophobia headers
#include "ObjectTree.h"

namespace av {
    class TreeIterator {
    private:
        // List of pointers for dynamically sized array
        const ObjectTree *p_tree;

        ObjectNode *p_node;
    public:
        // Constructor for the object list.
        TreeIterator(const ObjectTree *tree);

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

#endif // __TREEITERATOR_H__
