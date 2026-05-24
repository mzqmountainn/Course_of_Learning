// 分支限界算法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <queue>
using namespace std;

#if 0
int w[] = { 12, 8, 15 }; // 集装箱的重量
const int n = sizeof(w) / sizeof(w[0]); // 集装箱的数量
int c = 20; // 轮船的容量
int cw = 0; // 已选择物品的重量
int bestw = 0; // 记录最优的装载量

// 描述节点类型
struct Node {
	Node(int w, int l, Node *p, bool left) {
		weight = w;
		level = l;
		parent = p;
		isleft = left;
	}
	int weight; // 从根节点到当前节点所选择物品的总重量
	int level; // 当前节点的层数
	Node *parent; // 记录当前节点的父节点
	bool isleft;  // 记录当前节点是否被选择
};

// 广度优先遍历子集树的FIFO队列
queue<Node*> que;
int i = 0; // 表示起始的层数，从根节点开始
Node *bestnode = nullptr;
int r = 0; // 记录未被处理的物品的总重量

// 添加活结点到队列当中
void addLiveNode(int w, int level, Node *parent, bool isleft) {
	Node *node = new Node(w, level, parent, isleft);
	que.push(node);

	// 在最后一层，记录最优值节点
	if (level == n && w == bestw) {
		bestnode = node;
	}
}
// 节点的上界函数， 返回未被处理的物品的总重量
int maxBound(int level) {
	int s = 0;
	for (int j = level + 1; j < n; ++j) {
		s += w[j];
	}
	return s;
}
int main1()
{
	Node *node = nullptr; // 初始状态
	while (i < n) { // 当前节点是第i层     开始扩展node节点
		// 处理左孩子，表示选择i节点
		int wt = cw + w[i];
		if (wt <= c) { // 选择物品i以后，其总重量不能超过轮船的容量
			if (wt > bestw) {
				bestw = wt;
			}

			// 活结点孩子入队列
			// que.push(Node(cw + w[i], i + 1));
			addLiveNode(cw+w[i], i+1, node, true);
		}

		// 处理右孩子，表示不选择i节点
		// que.push(Node(cw, i + 1));
		r = maxBound(i); // 求第i个节点的重量值上界  
		if (cw + r >= bestw) { // >=这里的=操作不能少，否则无法选择到叶子节点上 c=20
			addLiveNode(cw, i + 1, node, false);
		}
		
		// 处理完i节点后，它成为死节点，然后出队
		node = que.front();
		que.pop();
		// 恢复cw和i的值，表示从i节点跳到广度遍历的下一个节点了
		cw = node->weight;
		i = node->level;
	}

	cout << bestw << endl;
	int bestx[n] = { 0 };
	for (int j = n - 1; j >= 0; --j) {
		bestx[j] = bestnode->isleft ? 1 : 0;
		bestnode = bestnode->parent;
	}
	for (int v : bestx) {
		cout << v << " ";
	}
	cout << endl;

	return 0;
}
#endif