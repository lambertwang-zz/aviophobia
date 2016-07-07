#pragma once
#ifndef __RBTREE_H__
#define __RBTREE_H__

// aviophobia headers
#include "HasId.h"
#include "RBNode.h"

namespace av {
    class RBTree {
    private:
        // The number of objects in the tree
        int count;
        // List of pointers for dynamically sized array
        RBNode *p_root;

        // Returns the index of where the object with the specified 
        // id is located or where it should be inserted.
        // int find(int id) const;
        // Copies another list into this list
        void copyFrom(const RBTree *to_copy);

        // Frees the memory allocated for this list
        void freeTree();

        // The tree is empty
        void insertCase1(RBNode *node);
        void insertCase2(RBNode *node);
        void insertCase3(RBNode *node);
        void insertCase4(RBNode *node);
        void insertCase5(RBNode *node);


        void deleteCase1(RBNode *node);
        void deleteCase2(RBNode *node);
        void deleteCase3(RBNode *node);
        void deleteCase4(RBNode *node);
        void deleteCase5(RBNode *node);
        void deleteCase6(RBNode *node);

        void replaceNode(RBNode *to_replace, RBNode *node);

    public:
        // Constructor for the object list.
        RBTree();

        // Copy operator
        RBTree(const RBTree *other);
        // Assignment operator
        RBTree &operator=(const RBTree *rhs);

        // Frees up allocated memory
        ~RBTree();

        // Returns the root of this tree
        RBNode *getRoot() const;

        // Insert an object pointer in the list
        // Returns true if successful, false otherwise
        // Maintains order on the list by object id
        // Performs a binary search for insertion sort
        int insert(HasId *obj);

        // Removes an object pointer from the list
        // Returns 0 if found -1 otherwise
        // Performs a binary search
        int remove(HasId *obj);

        int removeNode(RBNode *node);

        // Returns true if this list contains the object
        bool contains(HasId *obj) const;

        // Removes all objects from the list
        void clear();

        // Returns the number of objects in the list
        int getCount() const;

        // Returns whether the list is empty or not
        bool isEmpty() const;

        // Overload + operator for RBTrees
        RBTree operator+(RBTree list);
    };
} // End of namespace

#endif // __RBTREE_H__
