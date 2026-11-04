//
// Created by 18455 on 2026/10/18.
//
#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
using uint = unsigned int;

class Huffman {
public:
    Huffman() : nodeQueue_([](node *n1, node *n2)-> bool { return n1->weight_ > n2->weight_; }), head_(nullptr) {
        ;
    }

public:
    struct node {
        uint weight_;
        char data_;
        node *left_;
        node *right_;
        node(char data, uint weight) : data_(data), weight_(weight), left_(nullptr), right_(nullptr) { ; };
    };

    unordered_map<char, string> codeMap_;
    priority_queue<node *, vector<node *>, function<bool(node *, node *)> > nodeQueue_;
    void showHuffmanCode(void) {
        string code;
        showHuffmanCode(head_, code);
        for (auto &it: codeMap_) {
            cout << it.first << " " << it.second << endl;
        }
    }

public:
    void createHuffmanTree(string context);
    string encode(string data);
    string decode(string data);

private:
    node *head_;
    void showHuffmanCode(node *root, string code);
};

void Huffman::showHuffmanCode(node *root, string code) {
    if (root == nullptr)
        return;
    if (root->left_ == nullptr && root->right_ == nullptr) {
        codeMap_[root->data_] = code;
        return;
    }
    showHuffmanCode(root->left_, code + "0");
    showHuffmanCode(root->right_, code + "1");
}
void Huffman::createHuffmanTree(string context) {
    //首先统计权重
    unordered_map<char, uint> dataMap_;
    for (auto it: context) {
        dataMap_[it]++;
    }
    //生成节点 推入小根堆
    for (auto &pair: dataMap_) {
        nodeQueue_.push(new node(pair.first, pair.second));
    }
    if (nodeQueue_.empty()) {
        head_ = nullptr;
        return;
    }
    //生成树
    while (nodeQueue_.size() > 1) {
        node *n1 = nodeQueue_.top();
        nodeQueue_.pop();
        node *n2 = nodeQueue_.top();
        nodeQueue_.pop();
        node *father = new node('\0', n1->weight_ + n2->weight_);
        father->left_ = n1;
        father->right_ = n2;
        nodeQueue_.push(father);
    }
    head_ = nodeQueue_.top();
    nodeQueue_.pop();
}
string Huffman::encode(string data) {
    string codeing;
    for (auto it: data) {
        codeing += codeMap_[it];
    }
    return codeing;
}
string Huffman::decode(string data) {
    string decoding;
    node *cur = head_;
    for (auto it: data) {
        if (it == '0') {
            cur = cur->left_;
        } else {
            cur = cur->right_;
        }
        if (cur->left_ == nullptr && cur->right_ == nullptr) {
            decoding += cur->data_;
            cur = head_;
        }
    }
    return decoding;
}
int main() {
    Huffman tree;
    tree.createHuffmanTree("ABACDAEFDEG");
    tree.showHuffmanCode();
    cout << tree.encode("A") << endl;
    cout << tree.decode("111100");
    return 0;
}

