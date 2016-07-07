// aviophobia headers
#include "TreeIterator.h"

av::TreeIterator::TreeIterator(RBTree *tree) {
    this->p_tree = tree;
    this->p_current = tree->getRoot()->findMin();
}


void av::TreeIterator::first() {
    this->p_current = this->p_tree->getRoot()->findMin();
}

void av::TreeIterator::next() {
    if (this->isDone()) {
        return;
    }

    // if you can walk right, walk right, then fully left.
    // otherwise, walk up until you come from left.
    if (this->p_next->getRight()) {
        this->p_next = this->p_next->getRight();
        this->p_next = this->p_next->findMin();
        return;
    } else {
        while (true) {
            if (!this->p_next->getParent()) {
                this->p_next = nullptr;
                return;
            }
            if (this->p_next->getParent->getLeft() == next) {
                this->p_next = this->p_next->getParent();
                return;
            }
            this->p_next = this->p_next->getParent();
        }
    }
}

bool av::TreeIterator::isDone() const {
    return this->p_next != nullptr;
}
