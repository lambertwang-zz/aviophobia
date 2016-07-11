#pragma once
#ifndef __ObjectTree_H__
#define __ObjectTree_H__

// aviophobia headers
#include "ObjectNode.h"

namespace av {
    class ObjectTree {
    private:
        // The number of objects in the tree
        int count;
        // List of pointers for dynamically sized array
        ObjectNode *p_root;

        // Returns the index of where the object with the specified 
        // id is located or where it should be inserted.
        // int find(int id) const;
        // Copies another list into this list
        void copyFrom(const ObjectTree *to_copy);

        // Frees the memory allocated for this list
        void freeTree();

        // The tree is empty
        void insertCase1(ObjectNode *node);
        void insertCase2(ObjectNode *node);
        void insertCase3(ObjectNode *node);
        void insertCase4(ObjectNode *node);
        void insertCase5(ObjectNode *node);


        void deleteCase1(ObjectNode *node);
        void deleteCase2(ObjectNode *node);
        void deleteCase3(ObjectNode *node);
        void deleteCase4(ObjectNode *node);
        void deleteCase5(ObjectNode *node);
        void deleteCase6(ObjectNode *node);

        void replaceNode(ObjectNode *to_replace, ObjectNode *node);

    public:
        // Constructor for the object list.
        ObjectTree();

        // Copy operator
        ObjectTree(const ObjectTree *other);
        // Assignment operator
        ObjectTree &operator=(const ObjectTree *rhs);

        // Frees up allocated memory
        ~ObjectTree();

        // Returns the root of this tree
        ObjectNode *getRoot() const;

        // Insert an object pointer in the list
        // Returns true if successful, false otherwise
        // Maintains order on the list by object id
        // Performs a binary search for insertion sort
        int insert(Object *obj);

        // Removes an object pointer from the list
        // Returns 0 if found -1 otherwise
        // Performs a binary search
        int remove(Object *obj);

        int removeNode(ObjectNode *node);

        // Returns true if this list contains the object
        bool contains(Object *obj) const;

        // Removes all objects from the list
        void clear();

        // Returns the number of objects in the list
        int getCount() const;

        // Returns whether the list is empty or not
        bool isEmpty() const;

        // Overload + operator for ObjectTrees
        ObjectTree operator+(ObjectTree list);
    };
} // End of namespace

#endif // __ObjectTree_H__
