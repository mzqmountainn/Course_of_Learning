//
// Created by mzq on 2026/11/9.
//
#include <iostream>
#include <algorithm>
#include <list>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
using namespace std;
using uint = unsigned int;
const int INF = INT_MAX;

//此处使用邻接矩阵来描述图
int dijkstra(vector<vector<uint>>& graph, int start, int end)
{
    const int SIZE_GRAPH = graph.size();
    vector<uint> distance(graph.size(), INF);
    vector<bool> set(graph.size(), false); //0:u 1:s
    //initialization
    for (int i = 0; i < SIZE_GRAPH; i++)
    {
        distance[i] = graph[start][i];
    }
    for (int i = 1; i < SIZE_GRAPH; i++)
    {
        int k = -1;
        int min = INF;
        //search for minimum
        for (int j = 0; j < SIZE_GRAPH; j++)
        {
            if (!set[j] && min > distance[j])
            {
                k = j;
                min = distance[j];
            }
        }
        if (k == -1)
        {
            break;
        }
        set[k] = true;
        for (int j = 0; j < SIZE_GRAPH; j++)
        {
            //attention for the K J order
            if (!set[j] && min + graph[k][j] < distance[j])
            {
                distance[j] = min + graph[k][j];
            }
        }
    }

    return distance[end];
}

int dijkstra_priorityQueue(vector<vector<uint>>& graph, int start, int end)
{
    const int SIZE_GRAPH = graph.size();
    vector<uint> distance(graph.size(), INF);
    vector<bool> set(graph.size(), false); //0:u 1:s
    priority_queue<pair<uint, int>, vector<pair<uint, int>>, greater<pair<uint, int>>> que;
    //initialization
    for (int i = 0; i < SIZE_GRAPH; i++)
    {
        //distance[i] = graph[start][i];
        que.emplace(graph[start][i], i);
    }
    while (!que.empty())
    {
        auto pair = que.top();
        que.pop();
        if (pair.first == INF)
        {
            continue;
        }
        int k = pair.second;
        int min = pair.first;
        //search for minimum
        // for (int j = 0; j < SIZE_GRAPH; j++)
        // {
        //     if (!set[j] && min > distance[j])
        //     {
        //         k = j;
        //         min = distance[j];
        //     }
        // }
        // if (k == -1)
        // {
        //     break;
        // }
        set[k] = true;
        for (int j = 0; j < SIZE_GRAPH; j++)
        {
            //attention for the K J order
            if (!set[j] && min + graph[k][j] < distance[j])
            {
                distance[j] = min + graph[k][j];
                que.emplace(min + graph[k][j], j);
            }
        }
    }

    return distance[end];
}

int main(void)
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
    cout << dijkstra(graph, 0, 1);
    cout << dijkstra_priorityQueue(graph, 0, 1);
}

