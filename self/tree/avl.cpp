//
// Created by 18455 on 2026/7/29.
//

#include <iostream>
#include <cmath>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

template<typename T>
class AVLtree {
public:
    AVLtree(void) : root_(nullptr) {
    };
    //递归插入
    void insert(T &value) {
        root_ = insert(root_, value);
    }

private:
    struct Node {
        T data_;
        Node *leftChild_;
        Node *rightChild_;
        int height_;
        Node(T data = T()) : data_(data), leftChild_(nullptr), rightChild_(nullptr), height_(1) {
        };
    };

    Node *root_;

    //获取高度
    int height(Node *node) {
        return (node == nullptr) ? 0 : node->height_;
    }
    //右旋转操作
    Node *rightRotate(Node *node);
    Node *leftRotate(Node *node);
    Node *leftBalance(Node *node);
    Node *rightBalance(Node *node);
    Node *insert(Node *node, T &value);
};

//右旋转操作
template<typename T>
AVLtree<T>::Node *AVLtree<T>::rightRotate(Node *node) {
    //旋转操作
    Node *child = node->leftChild_;
    node->leftChild_ = child->rightChild_;
    child->rightChild_ = node;
    //更新层数
    node->height_ = std::max(height(node->leftChild_), height(node->rightChild_)) + 1;
    child->height_ = std::max(height(child->leftChild_), height(child->rightChild_)) + 1;
    return child;
}
//左旋转操作
template<typename T>
AVLtree<T>::Node *AVLtree<T>::leftRotate(Node *node) {
    //旋转操作
    Node *child = node->rightChild_;
    node->rightChild_ = child->leftChild_;
    child->leftChild_ = node;
    //更新层数
    node->height_ = std::max(height(node->leftChild_), height(node->rightChild_)) + 1;
    child->height_ = std::max(height(child->leftChild_), height(child->rightChild_)) + 1;
    return child;
}
//左平衡操作（左-右平衡）
template<typename T>
AVLtree<T>::Node *AVLtree<T>::leftBalance(Node *node) {
    node->leftChild_ = leftRotate(node->leftChild_);
    return rightRotate(node);
}
//右平衡操作（右-左平衡）
template<typename T>
AVLtree<T>::Node *AVLtree<T>::rightBalance(Node *node) {
    node->rightChild_ = rightRotate(node->rightChild_);
    return leftRotate(node);
}
//递归插入私有接口
template<typename T>
AVLtree<T>::Node *AVLtree<T>::insert(Node *node, T &value) {
    if (node == nullptr) {
        return new Node(value);
    }
    if (node->data_ > value) {
        node->leftChild_ = insert(node->leftChild_, value);
        if (height(node->leftChild_) - height(node->rightChild_) > 1) {
            //此时失衡
            //判断具体类型
            if (height(node->leftChild_->leftChild_) >= height(node->leftChild_->rightChild_)) {
                //左子树的左孩子高了
                node = rightRotate(node);
            } else {
                //此处为左子树的右孩子高了
                node = leftBalance(node);
            }
        }
    } else if (node->data_ < value) {
        node->rightChild_ = insert(node->rightChild_, value);
        if (height(node->rightChild_) - height(node->leftChild_) > 1) {
            //此时失衡
            //判断具体类型
            if (height(node->rightChild_->rightChild_) >= height(node->rightChild_->leftChild_)) {
                //右子树的右孩子高了
                node = leftRotate(node);
            } else {
                //此处为右子树的左孩子高了
                node = rightBalance(node);
            }
        }
    } else {
        //此时是有重复的情况 不插入 什么都不做
        ;
    }
    //高度更新
    node->height_ = std::max(height(node->leftChild_), height(node->rightChild_)) + 1;

    return node;
}
int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为 UTF-8
    SetConsoleCP(CP_UTF8); // 设置控制台输入为 UTF-8
#endif
    AVLtree<int> test1;

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (auto it: arr) {
        test1.insert(it);
    }
    return 0;
}
