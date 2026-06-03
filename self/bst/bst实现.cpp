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
        Node* rightchild;
        Node* root;
        Node()
    };

    Comp comp_;
};
