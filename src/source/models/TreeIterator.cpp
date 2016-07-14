// aviophobia headers
#include "TreeIterator.h"

av::TreeIterator::TreeIterator(const ObjectTree *tree) {
    this->p_tree = tree;
    if (!tree->isEmpty()) {
        this->p_node = tree->getRoot()->findMin();
    } else {
        this->p_node = NULL;
    }
}


void av::TreeIterator::first() {
    if (!this->p_tree->isEmpty()) {
        this->p_node = this->p_tree->getRoot()->findMin();
    } else {
        this->p_node = NULL;
    }
}

void av::TreeIterator::next() {
    if (this->isDone()) {
        return;
    }

    // if you can walk right, walk right, then fully left.
    // otherwise, walk up until you come from left.
    if (this->p_node->getRight()) {
        this->p_node = this->p_node->getRight();
        this->p_node = this->p_node->findMin();
        return;
    } else {
        while (true) {
            if (!this->p_node->getParent()) {
                this->p_node = nullptr;
                return;
            }
            if (this->p_node->getParent()->getLeft() == this->p_node) {
                this->p_node = this->p_node->getParent();
                return;
            }
            this->p_node = this->p_node->getParent();
        }
    }
}

bool av::TreeIterator::isDone() const {
    return this->p_node == NULL;
}

av::Object *av::TreeIterator::currentObject() const {
    if (!this->isDone()) {
        return this->p_node->getObj();
    }
    return NULL;
}
