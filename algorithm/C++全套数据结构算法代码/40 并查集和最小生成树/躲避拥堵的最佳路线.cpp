#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Road
{
	Road(int a, int b, int c)
		: u(a)
		, v(b)
		, w(c)
	{}
	int u;
	int v;
	int w;
};

const int SIZE = 10005;
int parent[SIZE];

int find(int x)
{
	if (x == parent[x])
		return x;
	return parent[x] = find(parent[x]);
}

void merge(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x != y)
	{
		parent[x] = y;
	}
}

int main()
{
	// 先初始化parent数组
	for (int i = 0; i < SIZE; i++)
	{
		parent[i] = i;
	}

	int n, m, s, t;
	cin >> n >> m >> s >> t;

	vector<Road> roads;
	int u, v, w;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		roads.emplace_back(u, v, w);
	}

	sort(roads.begin(), roads.end(),
		[](auto& a, auto& b)->bool {
			return a.w < b.w;
		});

	for (int i = 0; i < roads.size(); i++)
	{
		merge(roads[i].u, roads[i].v);
		// s和t区第一次有通路了
		if (find(s) == find(t))
		{
			cout << roads[i].w << endl;
			break;
		}
	}

	return 0;
}