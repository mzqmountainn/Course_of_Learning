// 39_图和最短路径算法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
using namespace std;

#if 0
// 实现一个有向图的邻接表结构
class Digraph
{
public:
	// 从配置文件读入顶点和边的信息，生成邻接表
	void readFile(string filePath)
	{
		FILE* pf = fopen(filePath.c_str(), "r");
		if (pf == nullptr)
		{
			throw filePath + " not exists!";
		}

		// 占用第0号位置
		vertics.emplace_back("");

		while (!feof(pf))
		{
			char line[1024] = { 0 };
			fgets(line, 1024, pf);
			// 增加一个节点信息
			string linestr(line);
			vertics.emplace_back(linestr.substr(0, linestr.size()-1));

			fgets(line, 1024, pf);
			char* vertic_no = strtok(line, ",");
			while (vertic_no != nullptr)
			{
				int vex = atoi(vertic_no);
				if (vex > 0)
				{
					vertics.back().adjList_.emplace_back(vex);
				}
				vertic_no = strtok(nullptr, ",");
			}
		}

		fclose(pf);
	}

	// 输出邻接表信息
	void show() const
	{
		for (int i = 1; i < vertics.size(); i++)
		{
			cout << vertics[i].data_ << " : ";
			for (auto no : vertics[i].adjList_)
			{
				cout << no << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	// 图的深度优先遍历
	void dfs()
	{
		vector<bool> visited(vertics.size(), false);
		dfs(1, visited);
		cout << endl;
	}

	// 广度优先遍历
	void bfs()
	{
		vector<bool> visited(vertics.size(), false);
		queue<int> que;

		que.push(1);
		visited[1] = true;

		while (!que.empty())
		{
			int cur_no = que.front();
			que.pop();

			cout << vertics[cur_no].data_ << " ";

			for (auto no : vertics[cur_no].adjList_)
			{
				if (!visited[no])
				{
					que.push(no);
					visited[no] = true;
				}
			}
		}
		cout << endl;
	}

	// 求不带权值的最短路径问题 - 广度优先遍历
	void shortPath(int start, int end)
	{
		vector<bool> visited(vertics.size(), false);
		queue<int> que;
		// 记录顶点在遍历过程中的前后遍历关系
		vector<int> path(vertics.size(), 0);

		que.push(start);
		visited[start] = true;

		while (!que.empty())
		{
			int cur_no = que.front();
			if (cur_no == end)
			{
				// 找到end末尾节点
				break;
			}
			que.pop();

			//cout << vertics[cur_no].data_ << " ";

			for (auto no : vertics[cur_no].adjList_)
			{
				if (!visited[no])
				{
					que.push(no);
					visited[no] = true;
					// 当前节点处，记录是从哪一个节点过来的
					path[no] = cur_no;
				}
			}
		}

		if (!que.empty())
		{
			// 存在一条最短路径，怎么输出？
			/*while (end != 0)
			{
				cout << vertics[end].data_ << " <= ";
				end = path[end];
			}*/
			showPath(end, path);
		}
		else
		{
			cout << "不存在有效的最短路径!" << endl;
		}
		cout << endl;
	}

private:
	// 深度优先遍历的递归接口
	void dfs(int start, vector<bool>& visited)
	{
		// 该start顶点已经遍历过了
		if (visited[start])
		{
			return;
		}

		cout << vertics[start].data_ << " ";
		visited[start] = true;

		// 递归遍历下一层节点
		for (auto no : vertics[start].adjList_)
		{
			dfs(no, visited);
		}
	}
	// 输出最短路径信息
	void showPath(int end, vector<int>& path)
	{
		if (end == 0)  // 已经回溯到起始节点了
			return;

		showPath(path[end], path);
		cout << vertics[end].data_ << " ";
	}
private:
	// 顶点类型
	struct Vertic
	{
		Vertic(string data)
			: data_(data)
		{}
		string data_;       // 存储顶点的信息
		list<int> adjList_; // 邻接链表结构
	};

private:
	vector<Vertic> vertics; // 邻接表结构
};

int main()
{
	Digraph graph;
	graph.readFile("data.txt");
	graph.show();
	graph.dfs();
	graph.bfs();

	cout << "================" << endl;
	graph.shortPath(1, 3);
	return 0;
}
#endif