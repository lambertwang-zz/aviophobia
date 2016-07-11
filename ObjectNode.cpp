// aviophobia headers
#include "ObjectNode.h"

void av::ObjectNode::copyFrom(const av::ObjectNode *to_copy) {
    this->freeTree();
    this->p_obj = to_copy->getObj();
    this->color = to_copy->getColor();
    this->parent = to_copy->getParent();
    av::ObjectNode *new_left = to_copy->getLeft(), *new_right = to_copy->getRight();
    if (new_left) {
        this->left = new av::ObjectNode(new_left);
    }
    if (new_right) {
        this->right = new av::ObjectNode(new_right);
    }
}

av::ObjectNode::ObjectNode(Object *obj, NodeColor color) {
    this->p_obj = obj;
    this->color = color;
    this->parent = nullptr;
    this->right = nullptr;
    this->left = nullptr;
}

av::ObjectNode::ObjectNode(const ObjectNode *other) {
    if (other) {
        this->copyFrom(other);
    }
}

void av::ObjectNode::freeTree() {
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

av::Object *av::ObjectNode::getObj() const {
    return this->p_obj;
}

void av::ObjectNode::setObj(Object * obj) {
    this->p_obj = obj;
}

av::NodeColor av::ObjectNode::getColor() const {
    return this->color;
}

int av::ObjectNode::getId() const {
    return this->p_obj->getId();
}

void av::ObjectNode::setColor(NodeColor new_color) {
    this->color = new_color;
}

av::ObjectNode *av::ObjectNode::find(Object * obj) {
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

av::ObjectNode *av::ObjectNode::findMin() {
    if (this->left) {
        return this->left->findMin();
    }
    return this;
}

av::ObjectNode *av::ObjectNode::findMax() {
    if (this->right) {
        return this->right->findMax();
    }
    return this;
}

av::ObjectNode *av::ObjectNode::findPredecessor() {
    if (this->left) {
        return this->left->findMax();
    }
    return nullptr;
}

av::ObjectNode * av::ObjectNode::findSuccessor() {
    if (this->right) {
        return this->right->findMin();
    }
    return nullptr;
}

int av::ObjectNode::insert(ObjectNode *n) {
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

av::ObjectNode *av::ObjectNode::getLeft() const {
    return this->left;
}

void av::ObjectNode::setLeft(ObjectNode *new_left) {
    this->left = new_left;
}

av::ObjectNode *av::ObjectNode::getRight() const {
    return this->right;
}

void av::ObjectNode::setRight(ObjectNode *new_right) {
    this->right = new_right;
}

av::ObjectNode *av::ObjectNode::getParent() const {
    if (this->parent) {
        return this->parent;
    }
    return nullptr;
}

void av::ObjectNode::setParent(ObjectNode *node) {
    this->parent = node;
}

av::ObjectNode *av::ObjectNode::getSibling() const {
    if (this->parent) {
        av::ObjectNode* parentRight = this->getParent()->getRight();
        if (parentRight == this) {
            return this->parent->getLeft();
        } else {
            return parentRight;
        }
    }
    return nullptr;
}

av::ObjectNode * av::ObjectNode::getGrandparent() const {
    if (this->parent) {
        return this->parent->getParent();
    }
    return nullptr;
}

av::ObjectNode * av::ObjectNode::getUncle() const {
    if (this->parent) {
        return this->parent->getSibling();
    }
    return nullptr;
}

av::ObjectNode * av::ObjectNode::getParentsSibling() const {
    return this->getUncle();
}

void av::ObjectNode::rotateLeft() {
    if (this->right) {
        ObjectNode *child = this->right;
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

void av::ObjectNode::rotateRight() {
    if (this->left) {
        ObjectNode *child = this->left;
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
