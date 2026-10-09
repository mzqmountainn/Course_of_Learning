//
// Created by 18455 on 2026/9/20.
//

#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <queue>
using namespace std;
// 分支限界算法 - 01背包问题     FIFO队列
int w[] = {16, 15, 15}; // 物品的重量
int v[] = {45, 25, 25}; // 物品的价值
int c = 31; // 背包的容量
const int n = sizeof(w) / sizeof(w[0]); // 物品的个数
int cw = 0; // 已选择物品的重量
int cv = 0; // 已选择物品的价值
int bestv = 0; // 装入背包的物品的最优价值

// 描述节点类型
struct Node {
    Node(int w, int v, int l, Node *p, bool left) {
        weight = w;
        value = v;
        level = l;
        parent = p;
        isleft = left;
    }
    int weight; // 已选择物品的总重量
    int value; // 已选择物品的总价值
    int level; // 节点所在的层数
    Node *parent; // 记录父节点
    bool isleft; // 节点是否被选择
};

Node *bestnode = nullptr; // 记录最优解的叶子节点
queue<Node *> que; // 广度遍历需要的FIFO队列
void addLiveNode(int w, int v, int l, Node *p, bool left) {
    Node *node = new Node(w, v, l, p, left);
    que.push(node);
    if (l == n && bestv == v) {
        bestnode = node;
    }
}
int getMaxBound(int level) {
    int s = 0;
    for (int i = level + 1; i < n; ++i) {
        s += v[i];
    }
    return s;
}
int main(void) {
    int i = 0;
    Node *node = nullptr;
    while (i < n) {
        int valueSelect = cv + v[i];
        int weightSelect = cw + w[i];
        if (weightSelect <= c) {
            if (valueSelect > bestv) {
                bestv = valueSelect;
            }
            addLiveNode(weightSelect, valueSelect, i + 1, node, true);
        }
        if (cv + getMaxBound(i) >= valueSelect) {
            addLiveNode(cw, cv, i + 1, node, false);
        }
        node = que.front();
        que.pop();
        cv = node->value;
        cw = node->weight;
        i = node->level;
    }
    cout << bestv << endl;
    int x[n] = {0};
    for (int j = n - 1; j >= 0; --j) {
        x[j] = bestnode->isleft ? 1 : 0;
        bestnode = bestnode->parent;
    }

    for (int v: x) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
