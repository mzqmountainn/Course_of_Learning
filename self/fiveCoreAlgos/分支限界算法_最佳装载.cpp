//
// Created by 18455 on 2026/9/20.
//
#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int level;
    int weight;
    Node *parent;
    bool isLeftChild;
    Node(int l, int w, Node *p, bool isLeft) : level(l), weight(w), parent(p), isLeftChild(isLeft) {
    }
};

int w[] = {12, 8, 15}; // 集装箱的重量
const int n = sizeof(w) / sizeof(w[0]); // 集装箱的数量
int c = 28; // 轮船的容量
int cw = 0; // 已选择物品的重量
int bestw = 0; // 记录最优的装载量
queue<Node *> q;
Node *bestnode = nullptr;
void addLiveNode(int level, int weight, Node *parent, bool isLeftChild) {
    Node *node = new Node(level, weight, parent, isLeftChild);
    q.push(node);
    // 在最后一层，记录最优值节点
    if (level == n && weight == bestw) {
        bestnode = node;
    }
}
int getMaxBound(int level) {
    int s = 0;
    for (int i = level + 1; i < n; ++i) {
        s += w[i];
    }
    return s;
};

int main() {
    int i = 0;
    Node *node = nullptr;
    while (i < n) {
        int ws = cw + w[i];
        if (ws <= c) {
            if (ws > bestw) {
                bestw = ws;
            }
            addLiveNode(i + 1, ws, node, true);
        }
        if (cw + getMaxBound(i) >= bestw) {
            addLiveNode(i + 1, cw, node, false);
        }
        node = q.front();
        q.pop();
        i = node->level;
        cw = node->weight;
    }
    cout << bestw;
    cout << endl;
    //通过bestnode追踪选择了哪些节点
    int bestx[n] = {0};
    Node *tempNode = bestnode;
    for (int j = n - 1; j >= 0; --j) {
        if (tempNode->isLeftChild == true) {
            bestx[j] = 1;
        }
        tempNode = tempNode->parent;
    }
    for (auto it: bestx) {
        cout << it << " ";
    }
}
