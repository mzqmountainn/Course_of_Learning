#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#if 0
// Kruskal算法实现 - 并查集的应用
// 边类型
struct Edge
{
	Edge(int s, int e, int c)
		: start(s)
		, end(e)
		, cost(c)
	{}
	int start; // 起始的节点
	int end;   // 末尾节点
	int cost;  // 边的权值
};

const int SIZE = 1000;
int parent[SIZE];

// 并查集 - 查询接口实现
int find(int x)
{
	if (x == parent[x])
		return x;
	return parent[x] = find(parent[x]);
}

int main()
{
	for (int i = 0; i < SIZE; i++)
	{
		parent[i] = i;
	}

	// 定义一个边数组
	vector<Edge> edges;
	int n;
	cin >> n;

	char s, e;
	int c;
	for (int i = 0; i < n; i++)
	{
		cin >> s >> e >> c;
		// 读取边的信息，添加到边数组中
		edges.emplace_back(s, e, c);
	}

	// 所有的边按权值小到大进行排序
	sort(edges.begin(), edges.end(),
		[](auto& a, auto& b)->bool {
			return a.cost < b.cost;
		});

	// 开始选边（按小到大进行选择）
	for (int i = 0; i < edges.size(); i++)
	{
		// 所谓选择边，就是合并这条边的两个顶点，但是前提是
		// 这两个顶点之前不在一颗树上(不在一个集合中)
		int a = find(edges[i].start);
		int b = find(edges[i].end);
		if (a != b)
		{
			// 可以进行合并
			parent[a] = b;
			printf("%c -> %c cost:%d \n", edges[i].start,
				edges[i].end, edges[i].cost);
		}
	}
}
#endif