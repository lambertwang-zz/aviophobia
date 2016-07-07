// standard headers
#include <stdlib.h>

// aviophobia headers
#include "HasId.h"
#include "RBTree.h"

void av::RBTree::copyFrom(const RBTree *to_copy) {
    this->freeTree();
    this->p_root = new RBNode(to_copy->getRoot());
}

void av::RBTree::freeTree() {
    if (this->p_root) {
        this->p_root->freeTree();
    }
    this->p_root = nullptr;
    this->count = 0;
}

void av::RBTree::insertCase1(RBNode *node) {
    if (!node->getParent()) {
        node->setColor(BLACK);
        return;
    }
    insertCase2(node);
}

void av::RBTree::insertCase2(RBNode *node) {
    if (node->getParent()->getColor() == BLACK) {
        return;
    }
    insertCase3(node);
}

void av::RBTree::insertCase3(RBNode * node) {
    RBNode *uncle = node->getUncle();

    if (uncle && (uncle->getColor() == RED)) {
        node->getParent()->setColor(BLACK);
        uncle->setColor(BLACK);
        RBNode *grandparent = node->getGrandparent();
        grandparent->setColor(RED);
        this->insertCase1(grandparent);
    } else {
        this->insertCase4(node);
    }
}

void av::RBTree::insertCase4(RBNode * node) {
    RBNode *grandparent = node->getGrandparent();

    RBNode *parent = node->getParent();
    if ((node == parent->getRight()) && (parent == grandparent->getLeft())) {
        // Left rotation
        /*
        RBNode *left = node->getLeft();
        grandparent->setLeft(node);
        node->setLeft(parent);
        parent->setRight(left);
        */
        parent->rotateLeft();

        node = node->getLeft();
    } else {
        if ((node == node->getParent()->getLeft()) && (node->getParent() == grandparent->getRight())) {
            // Right rotation
            /*
            RBNode *right = node->getRight();
            grandparent->setRight(node);
            node->setRight(parent);
            parent->setLeft(right);
            */
            parent->rotateRight();

            node = node->getRight();
        }
    }
    insertCase5(node);
}

void av::RBTree::insertCase5(RBNode *node) {
    RBNode *grandparent = node->getGrandparent();
    RBNode *parent = node->getParent();
    parent->setColor(BLACK);
    grandparent->setColor(RED);
    if (node == parent->getLeft()) {
        // Right rotation
        grandparent->rotateRight();
    } else {
        // Left rotation
        grandparent->rotateLeft();
    }
    if (this->p_root == grandparent) {
        this->p_root = parent;
        parent->setParent(NULL);
    }
}

void av::RBTree::deleteCase1(RBNode *node) {
    if (node->getParent()) {
        this->deleteCase2(node);
    }
}

void av::RBTree::deleteCase2(RBNode *node) {
    RBNode *sibling = node->getSibling();

    if (sibling->getColor() == RED) {
        node->getParent()->setColor(RED);
        sibling->setColor(BLACK);
        RBNode *parent = node->getParent();
        if (node == parent->getLeft()) {
            parent->rotateLeft();
        } else {
            parent->rotateRight();
        }
        if (parent == this->p_root) {
            this->p_root = sibling;
            sibling->setParent(NULL);
        }
    }
    this->deleteCase3(node);
}

void av::RBTree::deleteCase3(RBNode *node) {
    RBNode *sibling = node->getSibling();

    if ((node->getParent()->getColor() == BLACK) &&
        (sibling->getColor() == BLACK) &&
        (sibling->getLeft()->getColor() == BLACK) &&
        (sibling->getRight()->getColor() == BLACK)) {
        sibling->setColor(RED);
        this->deleteCase1(node->getParent());
    } else {
        this->deleteCase4(node);
    }
}

void av::RBTree::deleteCase4(RBNode *node) {
    RBNode *sibling = node->getSibling();

    if ((node->getParent()->getColor() == RED) &&
        (sibling->getColor() == BLACK) &&
        (sibling->getLeft()->getColor() == BLACK) &&
        (sibling->getRight()->getColor() == BLACK)) {
        sibling->setColor(RED);
        node->getParent()->setColor(BLACK);
    } else {
        this->deleteCase5(node);
    }
}

void av::RBTree::deleteCase5(RBNode *node) {
    RBNode *sibling = node->getSibling();

    if (sibling->getColor() == BLACK) { 
        /* this if statement is trivial,
        due to case 2 (even though case 2 changed the sibling to a sibling's child,
        the sibling's child can't be red, since no red parent can have a red child). */
        /* the following statements just force the red to be on the left of the left of the parent,
        or right of the right, so case six will rotate correctly. */
        if ((node == node->getParent()->getLeft()) &&
            (sibling->getRight()->getColor() == BLACK) &&
            (sibling->getLeft()->getColor() == RED)) { /* this last test is trivial too due to cases 2-4. */
            sibling->setColor(RED);
            sibling->getLeft()->setColor(BLACK);
            sibling->rotateRight();
        } else {
            if ((node == node->getParent()->getRight()) &&
                (sibling->getLeft()->getColor() == BLACK) &&
                (sibling->getRight()->getColor() == RED)) {/* this last test is trivial too due to cases 2-4. */
                sibling->setColor(RED);
                sibling->getRight()->setColor(BLACK);
                sibling->rotateLeft();
            }
        }
    }
    this->deleteCase6(node);
}

void av::RBTree::deleteCase6(RBNode * node) {
    RBNode *sibling = node->getSibling(), *parent = node->getParent();

    sibling->setColor(parent->getColor());
    parent->setColor(BLACK);

    if (node == parent->getLeft()) {
        sibling->getRight()->setColor(BLACK);
        parent->rotateLeft();
    } else {
        sibling->getLeft()->setColor(BLACK);
        parent->rotateRight();
    }
    if (this->p_root == parent) {
        this->p_root = sibling;
        sibling->setParent(NULL);
    }
}

void av::RBTree::replaceNode(RBNode *to_replace, RBNode *node) {
    // Precondition that to_replace has at most one non-null child
    RBNode *parent = to_replace->getParent();
    if (parent) {
        if (parent->getLeft() == to_replace) {
            parent->setLeft(node);
        } else {
            parent->setRight(node);
        }
        node->setParent(parent);
    } else {
        // If to_replace has no parents, it must be root
        this->p_root = node;
        node->setParent(NULL);
    }
}

av::RBTree::RBTree() {
    this->p_root = nullptr;
    this->count = 0;
}

av::RBTree::RBTree(const RBTree *other) {
    this->copyFrom(other);
}

av::RBTree &av::RBTree::operator=(const RBTree *rhs) {
    // Make sure objects aren't the same
    if (this != rhs) {
        // Free current list if allocated already
        this->freeTree();

        this->copyFrom(rhs);
    }
    return *this;
}

av::RBTree::~RBTree() {
    this->freeTree();
}

av::RBNode * av::RBTree::getRoot() const {
    return this->p_root;
}

int av::RBTree::insert(HasId *obj) {
    RBNode *new_node = new RBNode(obj, RED);
    if (!this->p_root) {
        this->p_root = new_node;
        this->insertCase1(new_node);
        this->count = 1;
        return 0;
    }
    if (this->p_root->insert(new_node)) {
        delete new_node;
        return -1;
    }
    this->insertCase1(new_node);
    this->count++;
    return 0;
}

int av::RBTree::remove(HasId *obj) {
    if (this->count == 0) {
        return -2; // No items to remove
    }

    return this->removeNode(this->p_root->find(obj));
}

int av::RBTree::removeNode(RBNode * node) {
    if (!node) {
        return -3; // Node does not exist in tree
    }

    // Node has no non-null children
    if (!node->getRight() && !node->getLeft()) {
        if (!node->getParent()) {
            this->p_root = nullptr;
        } else {
            if (node->getParent()->getLeft() == node) {
                node->getParent()->setLeft(nullptr);
            } else {
                node->getParent()->setRight(nullptr);
            }
        }
        this->count--;
        free(node);
        return 0;
    }

    // Node has two non-null children
    if (node->getRight() && node->getLeft()) {
        // Arbitrarily pick successor as nodes ids are strictly increasing, so it's slightly better to do so
        RBNode *successor = node->findSuccessor();
        node->setObj(successor->getObj());

        return this->removeNode(successor);
    }

    // Node has one child
    RBNode *child = node->getLeft() ? node->getLeft() : node->getRight();

    this->replaceNode(node, child);
    
    if (node->getColor() == BLACK) {
        if (child->getColor() == RED) {
            child->setColor(BLACK);
        } else {
            this->deleteCase1(child);
        }
    }

    this->count--;
    free(node);

    return 0;
}

bool av::RBTree::contains(HasId *obj) const {
    return p_root->find(obj) != NULL;
}

void av::RBTree::clear() {
    this->freeTree();
}

int av::RBTree::getCount() const {
    return this->count;
}

bool av::RBTree::isEmpty() const {
    return this->count == 0;
}

av::RBTree av::RBTree::operator+(RBTree list) {
    return RBTree();
}
