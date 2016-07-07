#pragma once
#ifndef __RBLEAF_H__
#define __RBLEAF_H__

// aviophobia headers
#include "HasId.h"

namespace av {

    enum NodeColor {
        RED, BLACK
    };

    class RBNode {
    private:
        // Pointer to object at this leaf
        HasId *p_obj;

        // The color of this node
        NodeColor color;

        // Left node
        RBNode *left;
        // Right node
        RBNode *right;
        // Parent node
        RBNode *parent;

        // Returns the index of where the object with the specified 
        // id is located or where it should be inserted.
        //int find(int id) const;
        // Copies another list into this list
        void copyFrom(const RBNode *to_copy);
    public:
        // Constructor for the leaf
        RBNode(HasId *obj, NodeColor color);

        // Copy operator
        RBNode(const RBNode *other);

        // Frees the memory allocated for this list
        void freeTree();

        HasId *getObj() const;

        void setObj(HasId *obj);

        NodeColor getColor() const;

        int getId() const;

        void setColor(NodeColor color);

        // Binary tree search
        RBNode *find(HasId *obj);

        // Finds the rightmost node in this subtree
        RBNode *findMin();

        // Finds the leftmost node in this subtree
        RBNode *findMax();

        // Find the in-order predecessor of this node
        RBNode *findPredecessor();

        // Find the in-order sucessor of this node
        RBNode *findSuccessor();

        // Binary tree insertion
        int insert(RBNode *n);

        // Retrieves this node's parent (if exists)
        // Otherwise returns null
        RBNode *getParent() const;

        // Sets the parent of this node
        void setParent(RBNode *parent);

        // Returns this node's left child (if exists)
        // Otherwise returns null
        RBNode *getLeft() const;

        // Sets the left of this node
        void setLeft(RBNode *left);

        // Returns this node's right child (if exists)
        // Otherwise returns null
        RBNode *getRight() const;

        // Sets the right of this node
        void setRight(RBNode *right);

        // Retrieves this node's sibling (if exists)
        // Otherwise returns null
        RBNode *getSibling() const;

        // Retrieves this node's parent's parent (if exists)
        // Otherwise returns null
        RBNode *getGrandparent() const;

        // Retrieves this node's grandparent's child that is not this node's parent
        // Returns null if doesn't exist
        RBNode *getUncle() const;

        // Passthrough for getUncle
        // To appease all those SJWs out there
        RBNode *getParentsSibling() const;

        void rotateLeft();

        void rotateRight();
    };
} // End of namespace

#endif // __RBLEAF_H__
