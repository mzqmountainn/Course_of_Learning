//
// Created by mzq on 2026/11/17.
//
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int SIZE = 100;
const int INF = INT_MAX;
int pointNumber; //顶点个数
int edgeNumber; //边个数
struct Edge
{
    int end;
    int cost;

    Edge(int e, int c) : end(e), cost(c)
    {
    };
};

vector<Edge> e[SIZE];
int flag[SIZE]; // 次算法中将点分为两个集合 0表示在未选中集合中 1表示在选中集合中
int distancePoint[SIZE]; //距离

bool prim(int x)
{
    int cnt = 0;
    for (int i = 0; i <= pointNumber; ++i)
    {
        distancePoint[i] = INF;
        flag[i] = 0;
    }
    //select x
    //flag[x] = 1;
    distancePoint[x] = 0;
    for (int i = 0; i < pointNumber; ++i)
    {
        int u = 0; //当前选点
        for (int j = 1; j <= pointNumber; ++j)
        {
            if (!flag[j] && distancePoint[j] < distancePoint[u])
            {
                u = j;
            }
        }
        flag[u] = 1;
        if (distancePoint[u] != INF)
        {
            cnt++;
            cout << u << " " << distancePoint[u] << endl;
        }
        //更新距离
        for (auto it : e[u])
        {
            if (distancePoint[it.end] > it.cost)
            {
                distancePoint[it.end] = it.cost;
            }
        }
    }
    return cnt == pointNumber;
}

bool prim_priority(int x)
{
    int cnt = 0;
    for (int i = 0; i <= pointNumber; ++i)
    {
        distancePoint[i] = INF;
        flag[i] = 0;
    }
    //select x
    //flag[x] = 1;
    distancePoint[x] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
    for (int i = 1; i <= pointNumber; ++i)
    {
        //初始化 全部压入小根堆
        que.emplace(distancePoint[i], i);
    }
    while (!que.empty())
    {
        int u = que.top().second; //当前选点
        int d = que.top().first; //当前选点的距离
        que.pop();
        if (!flag[u])
        {
            flag[u] = 1;
            if (distancePoint[u] != INF)
            {
                cnt++;
                cout << u << " " << distancePoint[u] << endl;
            }
        }
        // for (int j = 1; j <= pointNumber; ++j)
        // {
        //     if (!flag[j] && distancePoint[j] < distancePoint[u])
        //     {
        //         u = j;
        //     }
        // }
        // flag[u] = 1;

        //更新距离
        for (auto it : e[u])
        {
            if (distancePoint[it.end] > it.cost)
            {
                distancePoint[it.end] = it.cost;
                que.emplace(it.cost, it.end);
            }
        }
    }
    return cnt == pointNumber;
}

int main(void)
{
    cin >> pointNumber >> edgeNumber;
    for (int i = 0; i < edgeNumber; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        e[a].emplace_back(b, c);
        e[b].emplace_back(a, c);
    }
    // prim(1);
    prim_priority(1);
    return 0;
}

//test input
/*
5 7
1 2 2
1 3 1
1 4 2
2 3 1
2 5 3
3 4 3
3 5 6
*/
