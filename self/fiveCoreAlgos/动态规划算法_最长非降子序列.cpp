//
// Created by mzq on 2026/9/2.
//
#include <iostream>
#include <algorithm>
/*
朴素解法：不一定得到最优解，无效的解法     要求算法时间复杂度：O(n^2)
LIS问题：求序列的最长非降（升序）子序列的长度
5 3 4 1 8 7 9
状态：dp[i] 以第i个元素结尾的非降子序列的长度
状态转移方程：
dp[0] = 1
dp[1] = max{1,  1 + dp[0]} ar[0] <= ar[1] = 1
dp[2] = max{1,  1 + dp[1]}   ar[1] <= ar[2] = 2
...
dp[i] = max{1, 1 + dp[j]}  条件：ar[j] <= ar[i]  j号位元素和i号位元素才能构成非降子序列
*/
int arr[] = {5, 3, 4, 1, 8, 6, 7, 10};
const int length = sizeof(arr) / sizeof(arr[0]);
int max = 1;

int main(void)
{
    int* dp = new int[length + 1];
    dp[0] = 1;
    for (int i = 1; i < length; ++i)
    {
        dp[i] = 1;
        for (int j = 0; j < i; ++j)
        {
            if (arr[j] <= arr[i])
            {
                dp[i] = (1 + dp[j]) > dp[i] ? 1 + dp[j] : dp[i];
            }
        }
        if (dp[i] > max)
        {
            max = dp[i];
        }
    }
    std::cout << max;
    delete[]dp;
}
