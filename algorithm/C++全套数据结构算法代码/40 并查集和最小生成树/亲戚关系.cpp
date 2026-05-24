#include <iostream>
using namespace std;

#if 0
int n, m, p;

const int SIZE = 5001;
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
	cin >> n >> m >> p;

	for (int i = 1; i <= n; i++)
	{
		// 初始化每个节点的父节点是自己
		parent[i] = i;
	}

	int x, y;
	for (int i = 0; i < m; i++)
	{
		cin >> x >> y;
		merge(x, y);
	}

	for (int i = 0; i < p; i++)
	{
		cin >> x >> y;

		x = find(x);
		y = find(y);
		if (x == y)
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
	}
}
#endif