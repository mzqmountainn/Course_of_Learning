//
// Created by mzq on 2026/8/29.
//
//
// Created by mzq on 2026/8/27.
//
//挑选数字：有一组整数，请挑选出一组数字，让他们的和等于指定的值，存在解打印，不存在打印
#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>

using namespace std;
int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
const int sumTarget = 10;
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int> select;
vector<vector<int>> results;
int sum = 0;
//待处理的总和
int r = 0;


void func(int i)
{
    if (i == length)
    {
        if (sum == sumTarget)
        {
            results.push_back(select);
            for (auto it : select)
            {
                cout << it << " ";
            }
            cout << endl;
        }
    }
    else
    {
        if (sum + arr[i] <= sumTarget)
        {
            select.push_back(arr[i]);
            r -= arr[i];
            sum += arr[i];
            func(i + 1);
            sum -= arr[i];
            r += arr[i];
            select.pop_back();
        }
        if (sum + r >= sumTarget)
        {
            func(i + 1);
        }
    };
}

int main(void)
{
    for (auto it : arr)
    {
        r += it;
    }
    func(0);
    return 0;
}

