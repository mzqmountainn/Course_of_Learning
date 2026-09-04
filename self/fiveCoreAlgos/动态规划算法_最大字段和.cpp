//
// Created by mzq on 2026/9/2.
//
#include <iostream>
#include <algorithm>
using namespace std;

/*
最大子段和
状态：dp[i] 以第i个元素结尾的字段和的值
状态转移方程：
dp[0] = val < 0 ? 0 : val;  0
dp[1] = ar[1] + dp[0] = 11
dp[2] = ar[2] + dp[1] = -4 + 11 = 7
dp[3] = ar[3] + dp[2] = 13 + 7 = 20
...
dp[i] = ar[i] + dp[i-1]   i > 0  i==0子段和认为是已知的
*/

int arr[] = {-2, 11, -4, 13, -5, -2, 1};
const int length = sizeof(arr) / sizeof(arr[0]);
int maxval = 0;

int main(void)
{
    int* dp = new int[length + 1];
    dp[0] = arr[0] < 0 ? 0 : arr[0];
    for (int i = 1; i < length; ++i)
    {
        dp[i] = (dp[i - 1] + arr[i]);
        if (dp[i] < 0)
            dp[i] = 0;
        if (dp[i] > maxval)
            maxval = dp[i];
    }
    cout << maxval;
    delete[]dp;
}
