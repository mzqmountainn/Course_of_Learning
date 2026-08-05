//
// Created by 18455 on 2026/8/4.
//
#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

template<typename T>
class RBtree {
private:
    struct Node {
        enum color {
            BLACK, RED
        };

        Node *leftChild_;
        Node *rightChild_;
        Node *parent_;
        T data_;
        color color_;
        Node(T data = T(), Node *left = nullptr, Node *right = nullptr, Node *parent = nullptr,
             color colorIn = BLACK) : color_(colorIn), leftChild_(left), rightChild_(right), parent_(parent),
                                      data_(data) {
        }
    };

    Node *root_;
    void leftRotate(Node *node);
    void rightRotate(Node *node);

public:
    RBtree(void) : root_() {
    };
};

template<typename T>
void RBtree<T>::leftRotate(Node *node) {
    Node *child = node->rightChild_; //旋转关键1
    //如果node是根节点
    if (node->parent_ == nullptr) {
        root_ = child;
        child->parent_ = nullptr;
        node->parent_ = child;
    } else {
        child->parent_ = node->parent_;

        //判断左右
        if (node == node->parent_->leftChild_) {
            node->parent_->leftChild_ = child;
        } else {
            node->parent_->rightChild_ = child;
        }
        node->parent_ = child;
    }

    if (child->leftChild_ != nullptr) {
        child->leftChild_->parent_ = node;
    }
    node->rightChild_ = child->leftChild_; //旋转关键2

    child->leftChild_ = node; //旋转关键3
}
template<typename T>
void RBtree<T>::rightRotate(Node *node) {
    Node *child = node->leftChild_; // 旋转关键1

    // 如果node是根节点
    if (node->parent_ == nullptr) {
        root_ = child;
        child->parent_ = nullptr;
        node->parent_ = child;
    } else {
        child->parent_ = node->parent_;

        // 判断node原来是父节点的左孩子还是右孩子
        if (node == node->parent_->leftChild_) {
            node->parent_->leftChild_ = child;
        } else {
            node->parent_->rightChild_ = child;
        }

        node->parent_ = child;
    }

    // child原来的右子树挂到node的左边
    if (child->rightChild_ != nullptr) {
        child->rightChild_->parent_ = node;
    }

    node->leftChild_ = child->rightChild_; // 旋转关键2
    child->rightChild_ = node; // 旋转关键3
}
