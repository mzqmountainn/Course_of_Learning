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

public:
    RBtree(void) : root_() {
    };
};
