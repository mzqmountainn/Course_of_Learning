//
// Created by mzq on 2026/11/16.
//
#include <iostream>
#include <algorithm>
#include <list>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <algorithm>

using namespace std;
const int SIZE = 1000;
int parent[SIZE];

struct Edge
{
    int start;
    int end;
    int cost;

    Edge(int s, int e, int c) : start(s), end(e), cost(c)
    {
    };
};

int find(int x)
{
    if (x == parent[x])
    {
        return x;
    }
    return parent[x] = find(parent[x]);
}

int main(void)
{
    vector<Edge> edges;
    for (int i = 0; i < SIZE; ++i)
    {
        parent[i] = i;
    }
    int number = 0;
    cin >> number;
    for (int i = 0; i < number; ++i)
    {
        char s;
        char e;
        int c;
        cin >> s >> e >> c;
        edges.emplace_back(s, e, c);
    }
    sort(edges.begin(), edges.end(), [](auto& a, auto& b)-> bool { return a.cost < b.cost; });
    for (auto it : edges)
    {
        int a = find(it.start);
        int b = find(it.end);
        if (a != b)
        {
            parent[a] = b; //merge
            printf("%c -> %c  COST:%d", it.start, it.end, it.cost);
            cout << endl;
        }
    }
    return 0;
}
