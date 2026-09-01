//
// Created by mzq on 2026/9/1.
//
#include <iostream>
#include <algorithm>
using namespace std;

/*
硬币选择问题：有1，3，5分面额的硬币，给定一个面值11，问组成给定面值所需要的最少的硬币数量是多少？？？
11:    1 + (10)                                   3 + (8)                                5 + (6)
10:  1+(9)   3+(7)   5+(5)
                                           8:   1+(7)  3+(5)  5+(3)
                                                                                       6:   1+(5)  3+(3)  5+(1)
子问题的状态（最优解）: (9) 组成价值9需要的硬币的最少数量
dp[i]: 组成面值i需要的硬币最少数量
*/

#ifdef false
//递归解决问题 由分治算法演变
const int n = 100;
int dp[n + 1] = {0};

int func1(int n)
{
    if (dp[n] > 0)
    {
        return dp[n];
    }
    if (n == 1 || n == 3 || n == 5)
    {
        dp[n] = 1;
        return 1;
    }
    else if (n == 2 || n == 4)
    {
        dp[n] = 2;
        return 2;
    }
    else
    {
        int n1 = func1(n - 1) + 1;
        int n2 = func1(n - 3) + 1;
        int n3 = func1((n - 5)) + 1;
        dp[n] = min({n1, n2, n3});
        return dp[n];
    }
}

int main(void)
{
    cout << func1(n);
    return 0;
}
#else

#endif

int main(void)
{
    const int n = 260;
    //硬币大小
    int v[] = {1, 3, 5};
    int length = sizeof(v) / sizeof(v[0]);
    int* dp = new int[n + 1];
    dp[0] = 0;
    //进行核心操作
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = i;
        for (int j = 0; j < length; ++j)
        {
            if (i >= v[j])
            {
                dp[i] = min(dp[i], 1 + dp[i - v[j]]);
            }
        }
    }
    cout << dp[n];
    delete[]dp;
}
