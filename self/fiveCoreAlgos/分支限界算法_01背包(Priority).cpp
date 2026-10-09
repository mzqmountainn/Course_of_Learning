//
// Created by 18455 on 2026/9/20.
//

#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <queue>
using namespace std;
// 分支限界算法 - 01背包问题     Priority队列
int w[] = {16, 15, 15}; // 物品的重量
int v[] = {45, 25, 25}; // 物品的价值
int c = 31; // 背包的容量
const int n = sizeof(w) / sizeof(w[0]); // 物品的个数
int cw = 0; // 已选择物品的重量
int cv = 0; // 已选择物品的价值
int bestv = 0; // 装入背包的物品的最优价值

// 描述节点类型
struct Node {
    Node(int w, int v, int l, Node *p, bool left, int b) {
        weight = w;
        value = v;
        level = l;
        parent = p;
        isleft = left;
        upBound = b;
    }
    int weight; // 已选择物品的总重量
    int value; // 已选择物品的总价值
    int level; // 节点所在的层数
    Node *parent; // 记录父节点
    bool isleft; // 节点是否被选择
    int upBound;
};

Node *bestnode = nullptr; // 记录最优解的叶子节点
//优先级队列
priority_queue<Node *, vector<Node *>, function<bool(Node *, Node *)> > que([](Node *n1, Node *n2)-> bool {
    return n1->upBound < n2->upBound;
});
void addLiveNode(int w, int v, int l, Node *p, bool left, int b) {
    Node *node = new Node(w, v, l, p, left, b);
    que.push(node);
}
int getMaxBound(int level) {
    int s = cv;
    for (int i = level; i < n; ++i) {
        s += v[i];
    }
    return s;
}
int main(void) {
    int i = 0;
    Node *node = nullptr;
    int bound = getMaxBound(0);
    while (i < n) {
        int valueSelect = cv + v[i];
        int weightSelect = cw + w[i];
        if (weightSelect <= c) {
            if (valueSelect > bestv) {
                bestv = valueSelect;
            }
            addLiveNode(weightSelect, valueSelect, i + 1, node, true, bound);
        }
        bound = getMaxBound(i + 1);
        if (bound >= bestv) {
            addLiveNode(cw, cv, i + 1, node, false, bound);
        }
        node = que.top();
        que.pop();
        cv = node->value;
        cw = node->weight;
        i = node->level;
        bound = node->upBound;
    }
    cout << bestv << endl;
    int x[n] = {0};
    for (int j = n - 1; j >= 0; --j) {
        x[j] = node->isleft ? 1 : 0;
        node = node->parent;
    }

    for (int v: x) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
