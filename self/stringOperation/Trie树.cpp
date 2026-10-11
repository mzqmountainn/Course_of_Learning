//
// Created by 18455 on 2026/10/10.
//
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class TrieTree {
public:
    TrieTree() {
        root_ = new trieNode('\0', 0);
    };

    struct trieNode {
        trieNode(char data, int fre) : data_(data), frequency_(fre) {
        };
        char data_;
        int frequency_;
        map<char, trieNode *> nodeMap;
    };

    void add(const string &word);
    int query(const string &word);
    void preOrder();

private:
    trieNode *root_;
    void preOrder(trieNode *cur, string word, vector<string> &wordLists);
};

void TrieTree::preOrder() {
    vector<string> wordList;
    string word;
    preOrder(root_, word, wordList);
    for (auto it: wordList) {
        cout << it << endl;
    }
}
void TrieTree::preOrder(trieNode *cur, string word, vector<string> &wordLists) {
    if (cur != root_) {
        word += cur->data_;
    }
    if (cur->frequency_ != 0) {
        wordLists.emplace_back(word);
    }
    for (auto it: cur->nodeMap) {
        preOrder(it.second, word, wordLists);
    }
}

void TrieTree::add(const string &word) {
    trieNode *cur = root_;
    for (int i = 0; i < word.size(); ++i) {
        auto it = cur->nodeMap.find(word[i]);
        if (it == cur->nodeMap.end()) {
            auto newNode = new trieNode(word[i], 0);
            cur->nodeMap.emplace(word[i], newNode);
            cur = newNode;
        } else {
            cur = it->second;
        }
    }
    cur->frequency_++;
    return;
}
int TrieTree::query(const string &word) {
    trieNode *cur = root_;
    for (int i = 0; i < word.size(); ++i) {
        auto it = cur->nodeMap.find(word[i]);
        if (it == cur->nodeMap.end()) {
            return 0;
        } else {
            cur = it->second;
        }
    }
    return cur->frequency_;
}

int main(void) {
    TrieTree tree;
    tree.add("nice");
    tree.add("nicee");
    tree.add("npp");
    tree.add("nppp");
    tree.add("npp");
    tree.add("npp");
    tree.add("npp");
    tree.add("npp");
    cout << tree.query("nicee") << endl;
    tree.preOrder();
    return 0;
}
