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
    void fixAfterRemove(Node* node);

public:
    RBtree(void) : root_()
    {
    };
    ~RBtree();
    void insert(const T& val);
    void remove(const T& val);
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

template <typename T>
void RBtree<T>::fixAfterRemove(Node* node)
{
    while (node != root_ && getColor(node) == BLACK)
    {
        if (node->parent_->leftChild_ == node)
        {
            //左子树情况
            Node* brother = node->parent_->rightChild_;


            if (getColor(brother) == RED)
            {
                //情况4
                node->parent_->color_ = RED;
                brother->color_ = BLACK;
                leftRotate(node->parent_);
                brother = node->parent_->rightChild_;
            }
            if (getColor(brother->leftChild_) == BLACK && getColor(brother->rightChild_) == BLACK)
            {
                ///情况3
                brother->color_ = RED;
                node = node->parent_;
            }
            else
            {
                if (getColor(brother->rightChild_) == BLACK)
                {
                    //情况2
                    brother->color_ = RED;
                    brother->leftChild_->color_ = BLACK;
                    rightRotate(brother);
                    brother = node->parent_->rightChild_;
                }
                //情况1
                brother->color_ = node->parent_->color_;
                node->parent_->color_ = BLACK;
                brother->rightChild_->color_ = BLACK;
                leftRotate(node->parent_);
                break;
            }
        }
        else
        {
            //左子树情况
            Node* brother = node->parent_->leftChild_;
            if (getColor(brother) == RED)
            {
                //情况4
                node->parent_->color_ = RED;
                brother->color_ = BLACK;
                rightRotate(node->parent_);
                brother = node->parent_->leftChild_;
            }
            if (getColor(brother->rightChild_) == BLACK && getColor(brother->leftChild_) == BLACK)
            {
                ///情况3
                brother->color_ = RED;
                node = node->parent_;
            }
            else
            {
                if (getColor(brother->leftChild_) == BLACK)
                {
                    //情况2
                    brother->color_ = RED;
                    brother->rightChild_->color_ = BLACK;
                    leftRotate(brother);
                    brother = node->parent_->leftChild_;
                }
                //情况1
                brother->color_ = node->parent_->color_;
                node->parent_->color_ = BLACK;
                brother->leftChild_->color_ = BLACK;
                rightRotate(node->parent_);
                break;
            }
        }
    }
    node->color_ = BLACK;
}


template <typename T>
void RBtree<T>::remove(const T& val)
{
    Node* node = root_;
    while (node != nullptr)
    {
        if (val > node->data_)
        {
            node = node->rightChild_;
        }
        else if (val < node->data_)
        {
            node = node->leftChild_;
        }
        else
        {
            break;
        }
    }
    if (node == nullptr)
        return;
    //bst删除 三种情况 首先判断情况三：有两个孩子
    if (node->leftChild_ != nullptr && node->rightChild_ != nullptr)
    {
        Node* cur = node->leftChild_;
        while (cur->rightChild_ != nullptr)
        {
            cur = cur->rightChild_;
        }
        node->data_ = cur->data_;
        node = cur;
    }
    Node* child = node->leftChild_;
    if (child == nullptr)
    {
        child = node->rightChild_;
    }
    if (child != nullptr)
    {
        if (node->parent_ == nullptr)
        {
            delete node;
            root_ = child;
            child->parent_ = nullptr;
            child->color_ = BLACK;
            return;
        }
        //有一个孩子

        child->parent_ = node->parent_;
        if (node->parent_->leftChild_ == node)
        {
            node->parent_->leftChild_ = child;
        }
        else
        {
            node->parent_->rightChild_ = child;
        }
        color nodeColor = node->color_;
        delete node;
        //孩子是红色 直接涂黑
        if (nodeColor == BLACK)
        {
            //孩子是黑色 需要进一步调整
            if (getColor(child) == BLACK)
            {
                fixAfterRemove(child);
            }
            else
            {
                child->color_ = BLACK;
            }
        }
    }
    else
    {
        if (node->parent_ == nullptr)
        {
            delete node;
            root_ = nullptr;
            return;
        }

        if (getColor(node) == BLACK)
        {
            fixAfterRemove(node);
        }
        if (node->parent_->leftChild_ == node)
        {
            node->parent_->leftChild_ = nullptr;
        }
        else
        {
            node->parent_->rightChild_ = nullptr;
        }
        delete node;
        //没有孩子
    }
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
    test1.remove(1);
    for (auto it : arr)
    {
        test1.remove(it);
    }


    return 0;
}

