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

template<typename T, typename Comp = less<T>>

class BSTree {
private:
    struct Node {
        T data_;
        Node *leftChild;
        Node *rightChild;
        Node *root;
        Node(T data = T()) : data_(data), leftChild(nullptr), rightChild(nullptr) { ; }
    };

    Node *root_;
    Comp comp_;
public:
    BSTree(Comp c = Comp()) : root_(nullptr), comp_(c) { ; }
    //非递归插入
    void n_insert(T val) {
        if (root_ == nullptr) {
            root_ = new Node(val);
            return;
        }
        Node *cur = root_;
        Node *parent = nullptr;
        while (cur != nullptr) {
            //决定是否需要进入左孩子
            if (comp_(val, cur->data_)) {
                parent = cur;
                cur = cur->leftChild;
            } else if (val == cur->data_) {
                return;
            } else if (!comp_(val, cur->data_)) {
                parent = cur;
                cur = cur->rightChild;
            }//判断是否重复

        }
        cur = new Node(val);
        //判断插入左孩子还是右孩子
        if (comp_(val, parent->data_)) {
            parent->leftChild = cur;
        } else {
            parent->rightChild = cur;
        }
        cur = nullptr;
        return;
    }
};

int main(void) {
    BSTree<int> test1;
    int arr[] = {5, 4, 6, 2, 6, 7, 4, 99};
    for (auto i: arr) {
        test1.n_insert(i);
    }
    return 0;

}
