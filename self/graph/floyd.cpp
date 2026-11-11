//
// Created by mzq on 2026/11/10.
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

void floyd(vector<vector<uint>>& graph)
{
    for (int k = 0; k < graph.size(); ++k)
    {
        for (int i = 0; i < graph.size(); ++i)
        {
            for (int j = 0; j < graph.size(); ++j)
            {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }

    for (auto line : graph)
    {
        for (auto vex : line)
        {
            cout << vex << " ";
        }
        cout << endl;
    }
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
    floyd(graph);
}
