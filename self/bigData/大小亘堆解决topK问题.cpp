//
// Created by mzq on 2026/5/28.
//
#include <functional>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;
//Q1:大根堆实现最小的三个数
std::priority_queue<int> maxHeap;
//Q2:小根堆实现最大的三个数
priority_queue<int> minHeap;
//Q3:大根堆实现出现次数最少的三个数字
unordered_map<int, int> forMinNumMap;
using Type = pair<int, int>;
using Comp = function<bool(Type&, Type&)>;
priority_queue<Type, vector<Type>, Comp> maxHeap1([](Type& a, Type& b)-> bool
{
    return a.second < b.second;
});

int main(void)
{
    vector<int> vec;
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        vec.push_back(rand() % 100);
    }
#if 0
    for (int i = 0; i < 3; ++i)
    {
        maxHeap.push(vec[i]);
    }
    for (int i = 3; i < vec.size(); ++i)
    {
        if (maxHeap.top() > vec[i])
        {
            maxHeap.pop();
            maxHeap.push(vec[i]);
        }
    }
    while (!maxHeap.empty())
    {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
#endif

#if 0
    for (int i = 0; i < 3; ++i)
    {
        minHeap.push(vec[i]);
    }
    for (int i = 3; i < vec.size(); ++i)
    {
        if (minHeap.top() < vec[i])
        {
            minHeap.pop();
            minHeap.push(vec[i]);
        }
    }
    while (!minHeap.empty())
    {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
#endif
    for (auto it : vec)
    {
        forMinNumMap[it]++;
    }
    auto it = forMinNumMap.begin();
    for (int i = 0; i < 3; i++)
    {
        maxHeap1.push(*it);
        it++;
    }
    for (; it != forMinNumMap.end(); it++)
    {
        if (maxHeap1.top().second > it->second)
        {
            maxHeap1.pop();
            maxHeap1.push(*it);
        }
    }
    while (!maxHeap1.empty())
    {
        cout << "key:" << maxHeap1.top().first << "  ";
        cout << "cnt:" << maxHeap1.top().second << endl;
        maxHeap1.pop();
    }
}

