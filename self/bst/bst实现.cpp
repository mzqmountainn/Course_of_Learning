//
// Created by mzq on 2026/6/3.
//

#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

template <typename T, typename Comp = less<T>>

class BSTree
{
private:
    struct Node
    {
        T data_;
        Node* leftChild;
        Node* rightChild;
        Node* root;
        Node(T data = T()) : data_(data), leftChild(nullptr), rightChild(nullptr) { ; }
    };

    Node* root_;
    Comp comp_;

public:
    BSTree(Comp c = Comp()) : root_(nullptr), comp_(c) { ; }
    //非递归插入
    void n_insert(T const& val)
    {
        if (root_ == nullptr)
        {
            root_ = new Node(val);
            return;
        }
        Node* cur = root_;
        Node* parent = nullptr;
        while (cur != nullptr)
        {
            //决定是否需要进入左孩子
            if (comp_(val, cur->data_))
            {
                parent = cur;
                cur = cur->leftChild;
            }
            else if (val == cur->data_)
            {
                return;
            }
            else if (!comp_(val, cur->data_))
            {
                parent = cur;
                cur = cur->rightChild;
            } //判断是否重复
        }
        cur = new Node(val);
        //判断插入左孩子还是右孩子
        if (comp_(val, parent->data_))
        {
            parent->leftChild = cur;
        }
        else
        {
            parent->rightChild = cur;
        }
        cur = nullptr;
        return;
    }

    void n_remove(T const& val);
    bool n_query(T const& val);
};

/*
BST树删除节点
1.没有孩子的节点父节点地址域nullpt
2.有一个孩子孩子写入父节点地址域
3.删除的节点有两个孩子
找待删除节点的前驱节点（或者后继节点），用前驱或者后继节点的值把待删除节点的值覆盖
掉，然后直接删除前驱或者后继节点就可以了
*/
template <typename T, typename Comp>
void BSTree<T, Comp>::n_remove(T const& val)
{
    if (root_ == nullptr)
    {
        return;
    }
    //寻找删除节点
    Node* cur = root_;
    Node* parent = nullptr;
    while (cur != nullptr)
    {
        if (cur->data_ == val)
        {
            break;
        }
        else if (comp_(cur->data_, val))
        {
            parent = cur;
            cur = cur->rightChild;
        }
        else
        {
            parent = cur;
            cur = cur->leftChild;
        }
    }
    //为空说明找不到要删除的元素 结束
    if (cur == nullptr)
        return;
    Node* target = cur;

    //接下来开始判断是否属于情况3，判断是否有两个孩子
    if (cur->leftChild != nullptr && cur->rightChild != nullptr)
    {
        //寻找前驱节点
        parent = cur;
        cur = cur->leftChild;
        while (cur->rightChild != nullptr)
        {
            parent = cur;
            cur = cur->rightChild;
        }
        //将前驱节点的值和要删除的值交换
        target->data_ = cur->data_;
    }
    //进入删除，首先排除特殊情况：要删除的是root 且root左右孩子中只有一个孩子或者没有
    if (parent == nullptr && cur == root_)
    {
        if (root_->leftChild != nullptr)
        {
            parent = root_;
            root_ = root_->leftChild;
            delete parent;
            parent = nullptr;
        }
        else if ((root_->rightChild != nullptr))
        {
            parent = root_;
            root_ = root_->rightChild;
            delete parent;
            parent = nullptr;
        }
        else
        {
            delete root_;
            root_ = nullptr;
        }
        return;
    }
    //处理正常情况
    if (parent->leftChild == cur)
    {
        parent->leftChild = (cur->leftChild == nullptr ? cur->rightChild : cur->leftChild);
    }
    else if (parent->rightChild == cur)
    {
        parent->rightChild = (cur->leftChild == nullptr ? cur->rightChild : cur->leftChild);
    }
    delete cur;
}

template <typename T, typename Comp>
bool BSTree<T, Comp>::n_query(T const& val)
{
    Node* cur = root_;
    while (cur != nullptr)
    {
        if (cur->data_ == val)
        {
            return true;
        }
        else if (comp_(cur->data_, val))
        {
            cur = cur->rightChild;
        }
        else
        {
            cur = cur->leftChild;
        }
    }
    return false;
}

int main(void)
{
    BSTree<int> test1;
    int arr[] = {5, 4, 6, 2, 6, 7, 4, 99};
    for (auto i : arr)
    {
        test1.n_insert(i);
    }
    // test1.n_insert(5);
    // test1.n_insert(4);
    // test1.n_insert(6);
    cout << test1.n_query(7);
    test1.n_remove(7);
    cout << test1.n_query(7);
    cout << test1.n_query(66);
    cout << test1.n_query(99);

    return 0;
}
