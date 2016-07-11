#pragma once
#ifndef __RBLEAF_H__
#define __RBLEAF_H__

// aviophobia headers
#include "Object.h"

namespace av {

    enum NodeColor {
        RED, BLACK
    };

    class ObjectNode {
    private:
        // Pointer to object at this leaf
        Object *p_obj;

        // The color of this node
        NodeColor color;

        // Left node
        ObjectNode *left;
        // Right node
        ObjectNode *right;
        // Parent node
        ObjectNode *parent;

        // Returns the index of where the object with the specified 
        // id is located or where it should be inserted.
        //int find(int id) const;
        // Copies another list into this list
        void copyFrom(const ObjectNode *to_copy);
    public:
        // Constructor for the leaf
        ObjectNode(Object *obj, NodeColor color);

        // Copy operator
        ObjectNode(const ObjectNode *other);

        // Frees the memory allocated for this list
        void freeTree();

        Object *getObj() const;

        void setObj(Object *obj);

        NodeColor getColor() const;

        int getId() const;

        void setColor(NodeColor color);

        // Binary tree search
        ObjectNode *find(Object *obj);

        // Finds the rightmost node in this subtree
        ObjectNode *findMin();

        // Finds the leftmost node in this subtree
        ObjectNode *findMax();

        // Find the in-order predecessor of this node
        ObjectNode *findPredecessor();

        // Find the in-order sucessor of this node
        ObjectNode *findSuccessor();

        // Binary tree insertion
        int insert(ObjectNode *n);

        // Retrieves this node's parent (if exists)
        // Otherwise returns null
        ObjectNode *getParent() const;

        // Sets the parent of this node
        void setParent(ObjectNode *parent);

        // Returns this node's left child (if exists)
        // Otherwise returns null
        ObjectNode *getLeft() const;

        // Sets the left of this node
        void setLeft(ObjectNode *left);

        // Returns this node's right child (if exists)
        // Otherwise returns null
        ObjectNode *getRight() const;

        // Sets the right of this node
        void setRight(ObjectNode *right);

        // Retrieves this node's sibling (if exists)
        // Otherwise returns null
        ObjectNode *getSibling() const;

        // Retrieves this node's parent's parent (if exists)
        // Otherwise returns null
        ObjectNode *getGrandparent() const;

        // Retrieves this node's grandparent's child that is not this node's parent
        // Returns null if doesn't exist
        ObjectNode *getUncle() const;

        // Passthrough for getUncle
        // To appease all those SJWs out there
        ObjectNode *getParentsSibling() const;

        void rotateLeft();

        void rotateRight();
    };
} // End of namespace

#endif // __RBLEAF_H__
