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

template <typename T>
class RBtree
{
private:
    enum color
    {
        BLACK, RED
    };

    struct Node
    {
        Node* leftChild_;
        Node* rightChild_;
        Node* parent_;
        T data_;
        color color_;

        Node(T data = T(), Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr,
             color colorIn = BLACK) : color_(colorIn), leftChild_(left), rightChild_(right), parent_(parent),
                                      data_(data)
        {
        }
    };

    Node* root_;
    void leftRotate(Node* node);
    void rightRotate(Node* node);

    color getColor(Node* node)
    {
        return (node == nullptr) ? BLACK : node->color_;
    }

    void fixAfterInsert(Node* node);
    Node* parent(Node* node) { return node->parent_; }
    Node* left(Node* node) { return node->leftChild_; }
    Node* right(Node* node) { return node->rightChild_; }
    void destroy(Node* node);

public:
    RBtree(void) : root_()
    {
    };
    ~RBtree();
    void insert(const T& val);
};

template <typename T>
void RBtree<T>::leftRotate(Node* node)
{
    Node* child = node->rightChild_; //旋转关键1
    //如果node是根节点
    if (node->parent_ == nullptr)
    {
        root_ = child;
        child->parent_ = nullptr;
        node->parent_ = child;
    }
    else
    {
        child->parent_ = node->parent_;

        //判断左右
        if (node == node->parent_->leftChild_)
        {
            node->parent_->leftChild_ = child;
        }
        else
        {
            node->parent_->rightChild_ = child;
        }
        node->parent_ = child;
    }

    if (child->leftChild_ != nullptr)
    {
        child->leftChild_->parent_ = node;
    }
    node->rightChild_ = child->leftChild_; //旋转关键2

    child->leftChild_ = node; //旋转关键3
}

template <typename T>
void RBtree<T>::rightRotate(Node* node)
{
    Node* child = node->leftChild_; // 旋转关键1

    // 如果node是根节点
    if (node->parent_ == nullptr)
    {
        root_ = child;
        child->parent_ = nullptr;
        node->parent_ = child;
    }
    else
    {
        child->parent_ = node->parent_;

        // 判断node原来是父节点的左孩子还是右孩子
        if (node == node->parent_->leftChild_)
        {
            node->parent_->leftChild_ = child;
        }
        else
        {
            node->parent_->rightChild_ = child;
        }

        node->parent_ = child;
    }

    // child原来的右子树挂到node的左边
    if (child->rightChild_ != nullptr)
    {
        child->rightChild_->parent_ = node;
    }

    node->leftChild_ = child->rightChild_; // 旋转关键2
    child->rightChild_ = node; // 旋转关键3
}

template <typename T>
void RBtree<T>::insert(const T& val)
{
    //正常插入流程
    Node* node = nullptr;
    Node* cur = root_;
    Node* parent = nullptr;
    if (root_ == nullptr)
    {
        node = new Node(val);
        root_ = node;
        root_->color_ = BLACK;
        return;
    }
    else
    {
        cur = root_;
        while (cur != nullptr)
        {
            if (val > cur->data_)
            {
                parent = cur;
                cur = cur->rightChild_;
            }
            else if (val < cur->data_)
            {
                parent = cur;
                cur = cur->leftChild_;
            }
            else
            {
                //此时重复了 不执行插入
                return;
            }
        }
        node = new Node(val);
        node->color_ = RED;
        //进行插入
        if (val > parent->data_)
        {
            parent->rightChild_ = node;
        }
        else
        {
            parent->leftChild_ = node;
        }

        node->parent_ = parent;
    }
    //判断是否满足红黑树的性质
    //接下来开始按照红黑树插入的三种（一共六种 左右三种）情况进行判断 首先判断左右
    if (getColor(parent) == RED)
    {
        fixAfterInsert(node);
    }
}

template <typename T>
void RBtree<T>::fixAfterInsert(Node* node)
{
    while (getColor(node->parent_) == RED)
    {
        //首先判断左右子树()
        if (node->parent_->parent_->leftChild_ == node->parent_)
        {
            //左
            if (getColor(node->parent_->parent_->rightChild_) == RED)
            {
                //情况1
                node->parent_->color_ = BLACK;
                node->parent_->parent_->color_ = RED;
                node->parent_->parent_->rightChild_->color_ = BLACK;
                node = node->parent_->parent_;
            }
            else
            {
                //情况2，3 其中先判断情况3
                if (node == node->parent_->rightChild_)
                {
                    leftRotate(node->parent_);
                    node = node->leftChild_;
                }
                node->parent_->color_ = BLACK;
                node->parent_->parent_->color_ = RED;
                rightRotate(node->parent_->parent_);
            }
        }
        else
        {
            //右
            if (getColor(node->parent_->parent_->leftChild_) == RED)
            {
                //情况1
                node->parent_->color_ = BLACK;
                node->parent_->parent_->color_ = RED;
                node->parent_->parent_->leftChild_->color_ = BLACK;
                node = node->parent_->parent_;
            }
            else
            {
                //情况2，3 其中先判断情况3
                if (node == node->parent_->leftChild_)
                {
                    rightRotate(node->parent_);
                    node = node->rightChild_;
                }
                node->parent_->color_ = BLACK;
                node->parent_->parent_->color_ = RED;
                leftRotate(node->parent_->parent_);
            }
        }
        root_->color_ = BLACK;
    }
}

template <typename T>
RBtree<T>::~RBtree()
{
    destroy(root_);
    root_ = nullptr;
}

template <typename T>
void RBtree<T>::destroy(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    destroy(node->leftChild_);
    destroy(node->rightChild_);

    delete node;
}

int main(void)
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为 UTF-8
    SetConsoleCP(CP_UTF8); // 设置控制台输入为 UTF-8
#endif
    RBtree<int> test1;

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (auto it : arr)
    {
        test1.insert(it);;
    }


    return 0;
}

