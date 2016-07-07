// aviophobia headers
#include "RBNode.h"

void av::RBNode::copyFrom(const av::RBNode *to_copy) {
    this->freeTree();
    this->p_obj = to_copy->getObj();
    this->color = to_copy->getColor();
    this->parent = to_copy->getParent();
    av::RBNode *new_left = to_copy->getLeft(), *new_right = to_copy->getRight();
    if (new_left) {
        this->left = new av::RBNode(new_left);
    }
    if (new_right) {
        this->right = new av::RBNode(new_right);
    }
}

av::RBNode::RBNode(HasId *obj, NodeColor color) {
    this->p_obj = obj;
    this->color = color;
    this->parent = nullptr;
    this->right = nullptr;
    this->left = nullptr;
}

av::RBNode::RBNode(const RBNode *other) {
    if (other) {
        this->copyFrom(other);
    }
}

void av::RBNode::freeTree() {
    if (this->left) {
        delete this->left;
        this->left = nullptr;
    }
    if (this->right) {
        delete this->right;
        this->right = nullptr;
    }
    delete this;
}

av::HasId *av::RBNode::getObj() const {
    return this->p_obj;
}

void av::RBNode::setObj(HasId * obj) {
    this->p_obj = obj;
}

av::NodeColor av::RBNode::getColor() const {
    return this->color;
}

int av::RBNode::getId() const {
    return this->p_obj->getId();
}

void av::RBNode::setColor(NodeColor new_color) {
    this->color = new_color;
}

av::RBNode *av::RBNode::find(HasId * obj) {
    if (obj->getId() == this->getId()) {
        return this;
    } else {
        if (obj->getId() < this->getId()) {
            if (this->left) {
                return this->left->find(obj);
            }
        } else {
            if (obj->getId() > this->getId()) {
                if (this->right) {
                    return this->right->find(obj);
                }
            }
        }
    }
    return nullptr;
}

av::RBNode *av::RBNode::findMin() {
    if (this->left) {
        return this->left->findMin();
    }
    return this;
}

av::RBNode *av::RBNode::findMax() {
    if (this->right) {
        return this->right->findMax();
    }
    return this;
}

av::RBNode *av::RBNode::findPredecessor() {
    if (this->left) {
        return this->left->findMax();
    }
    return nullptr;
}

av::RBNode * av::RBNode::findSuccessor() {
    if (this->right) {
        return this->right->findMin();
    }
    return nullptr;
}

int av::RBNode::insert(RBNode *n) {
    if (n->getId() > this->getId()) {
        if (this->right) {
            return this->right->insert(n);
        } else {
            this->right = n;
            n->setParent(this);
        }
    } else {
        if (n->getId() < this->getId()) {
            if (this->left) {
                return this->left->insert(n);
            } else {
                this->left = n;
                n->setParent(this);
            }
        } else {
            return -1;
        }
    }
    return 0;
}

av::RBNode *av::RBNode::getLeft() const {
    return this->left;
}

void av::RBNode::setLeft(RBNode *new_left) {
    this->left = new_left;
}

av::RBNode *av::RBNode::getRight() const {
    return this->right;
}

void av::RBNode::setRight(RBNode *new_right) {
    this->right = new_right;
}

av::RBNode *av::RBNode::getParent() const {
    if (this->parent) {
        return this->parent;
    }
    return nullptr;
}

void av::RBNode::setParent(RBNode *node) {
    this->parent = node;
}

av::RBNode *av::RBNode::getSibling() const {
    if (this->parent) {
        av::RBNode* parentRight = this->getParent()->getRight();
        if (parentRight == this) {
            return this->parent->getLeft();
        } else {
            return parentRight;
        }
    }
    return nullptr;
}

av::RBNode * av::RBNode::getGrandparent() const {
    if (this->parent) {
        return this->parent->getParent();
    }
    return nullptr;
}

av::RBNode * av::RBNode::getUncle() const {
    if (this->parent) {
        return this->parent->getSibling();
    }
    return nullptr;
}

av::RBNode * av::RBNode::getParentsSibling() const {
    return this->getUncle();
}

void av::RBNode::rotateLeft() {
    if (this->right) {
        RBNode *child = this->right;
        if (child->getLeft()) {
            this->right = child->getLeft();
            child->getLeft()->setParent(this);
        } else {
            this->right = nullptr;
        }
        child->setLeft(this);
        if (this->parent) {
            if (this->parent->getLeft() == this) {
                this->parent->setLeft(child);
            } else {
                this->parent->setRight(child);
            }
            child->setParent(this->parent);
        }
        this->parent = child;
    }
}

void av::RBNode::rotateRight() {
    if (this->left) {
        RBNode *child = this->left;
        if (child->getRight()) {
            this->left = child->getRight();
            child->getRight()->setParent(this);
        } else {
            this->left = nullptr;
        }
        child->setRight(this);
        if (this->parent) {
            if (this->parent->getLeft() == this) {
                this->parent->setLeft(child);
            } else {
                this->parent->setRight(child);
            }
            child->setParent(this->parent);
        }
        this->parent = child;
    }
}
