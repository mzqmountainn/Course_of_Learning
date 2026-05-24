// 40 并查集和最小生成树.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#if 0
const int SIZE = 9;
int parent[SIZE]; // 记录每个节点的父节点(经过优化后记录树的根节点编号)
int rank[SIZE];   // 记录节点的层高

// 并查集-查询方法。返回参数x节点所在树的根节点的编号
int non_find(int x)
{
	// int pos = x;
	while (x != parent[x])
	{
		// x更新成其父节点的编号
		x = parent[x];
	}

	// 树根是x。把执行查询操作的时候将访问过的每个点的父节点修改成树根
	// parent[pos] = x;

	return x;
}
// 并查集-查询方法。递归版本实现
int find(int x)
{
	if (x == parent[x])
	{
		return x;
	}
	// 把执行查询操作的时候将访问过的每个点的父节点修改成树根
	return parent[x] = find(parent[x]);
}

// 并查集-union合并方法
// x和y原来不在一个集合中，才需要合并；如果已经在一个集合中了，不需要合并
void merge(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x != y)
	{
		if (rank[x] > rank[y])
		{
			parent[y] = x;
		}
		else
		{
			if (rank[x] == rank[y])
			{
				// y作为合并以后的集合树的根，rank值要+1
				rank[y]++;
			}
			// 合并两个集合
			parent[x] = y;
		}
	}
}

int main()
{
	// 数组初始化，存储当前节点自己的编号
	for (int i = 0; i < SIZE; i++)
	{
		parent[i] = i;
		rank[i] = 1;  
	}

	/*
1 3
1 2
5 4
2 4
6 8
8 7
	*/
	int x, y;
	for (int i = 0; i < 6; i++)
	{
		cin >> x >> y;
		merge(x, y);
	}

	cout << (find(2) == find(4) ? "OK" : "NO") << endl;
}
#endif