#include <iostream>
#include <vector>
#include <queue>
using namespace std;


#if 0
using uint = unsigned int;
const uint INF = INT_MAX;


#if 0
// 迪杰斯特拉算法接口
int Dijkstra(vector<vector<uint>>& graph,
			 int start,  // 起点 
			 int end)    // 终点
{
	const int N = graph.size();
	// 存储各个顶点的最短路径(最小权值)
	vector<uint> dis(N, 0);
	vector<bool> use(N, false);

	// 把start放入S集合
	use[start] = true;
	// 初始化start到其它U集合顶点权值
	for (int i = 0; i < N; i++)
	{
		dis[i] = graph[start][i];
	}

	// 把U集合中的顶点处理完  
	for (int i = 1; i < N; i++)    // O(n)
	{
		// 先从U集合中找到权值最小的顶点   
		int k = -1;
		int min = INF;
		for (int j = 0; j < N; j++)  // O(n)
		{
			if (!use[j] && min > dis[j]) // U集合的顶点
			{
				min = dis[j];
				k = j;
			}
		}

		if (k == -1)
		{
			break;
		}

		// 把选出的顶点加入到S集合中
		use[k] = true;

		// 把U集合中剩余顶点的权值信息更新一下
		for (int j = 0; j < N; j++)
		{
			if (!use[j] && min + graph[k][j] < dis[j]) // U集合
			{
				dis[j] = min + graph[k][j];
			}
		}
	}

	// 测试打印
	for (int d : dis)
	{
		cout << d << " ";
	}
	cout << endl;

	return dis[end];
}
#endif

// 迪杰斯特拉算法接口-优化
int Dijkstra(vector<vector<uint>>& graph,
	int start,  // 起点 
	int end)    // 终点
{
	const int N = graph.size();
	// 存储各个顶点的最短路径(最小权值)
	vector<uint> dis(N, 0);
	vector<bool> use(N, false);

	// 定义小根堆
	priority_queue<pair<uint, int>, vector<pair<uint, int>>, greater<pair<uint, int>>> que;

	// 把start放入S集合
	use[start] = true;
	// 初始化start到其它U集合顶点权值
	for (int i = 0; i < N; i++)
	{
		dis[i] = graph[start][i];
		// 把除start顶点的其它顶点全部放入U集合小根堆中
		if (i != start)
		{
			que.emplace(graph[start][i], i);
		}
	}

	// 把U集合中的顶点处理完  
	while (!que.empty())    // O(n)
	{
		// 用小根堆找权值最小的顶点    O(logn)   pair<权值，顶点编号>
		// 先从U集合中找到权值最小的顶点   
		auto pair = que.top();
		que.pop();
		if (pair.first == INF)
		{
			break;
		}
		int k = pair.second;
		int min = pair.first;

		if (use[k])  
			continue;
		// 把选出的顶点加入到S集合中
		use[k] = true;

		// 把U集合中剩余顶点的权值信息更新一下
		for (int j = 0; j < N; j++)
		{
			if (!use[j] && min + graph[k][j] < dis[j]) // U集合
			{
				dis[j] = min + graph[k][j];
				// 更新U集合中顶点的权值！
				que.emplace(dis[j], j);
			}
		}
	}

	// 测试打印
	for (int d : dis)
	{
		cout << d << " ";
	}
	cout << endl;

	return dis[end];
}

int main()
{
	vector<vector<uint>> graph =
	{
		{0, 6, 3, INF, INF, INF},
		{6, 0, 2, 5, INF, INF},
		{3, 2, 0, 3, 4, INF},
		{INF, 5, 3, 0, 2, 3},
		{INF, INF, 4, 2, 0, 5},
		{INF, INF, INF, 3, 5, 0},
	};

	int distance = Dijkstra(graph, 0, 1);
	if (distance == INF)
	{
		cout << "不存在有效路径!" << endl;
	}
	else
	{
		cout << "distance:" << distance << endl;
	}
}
#endif