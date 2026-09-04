//
// Created by mzq on 2026/9/4.
//

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

/*
LCS：求两个序列的最长公共子序列的长度   子串（连续的）
helloworld
   hlweord

helloworl  hlweord   => 情况1
helloworlr  hlweor    => 情况2

X : X1,X2...Xn
Y:  Y1,Y2...Ym

状态的转移方程
如果Xn == Ym
dp(X[1...n],Y[1...m]) = dp(X[1...n-1], Y[1...m-1]) + 1
如果Xn != Ym
dp(X[1...n],Y[1...m]) = max{dp(X[1...n],Y[1...m-1]) ,  dp(X[1...n-1],Y[1...m]) }

状态：给定的两个序列的LCS的长度
dp[n][m] : n表示第一个串的长度   m表示第二个串的长度，n行m列元素的值，记录的就是这两个串的LCS长度
*/
//递归解法

string str1 = "helloworld";
string str2 = "hwelloworld";
int** dp = nullptr;

int func(string str1, int n, string str2, int m)
{
   if (m < 0 || n < 0)
   {
      return 0;
   }
   if (dp[n][m] > 0)
   {
      return dp[n][m];
   }
   if (str1[n] == str2[m])
   {
      dp[n][m] = func(str1, n - 1, str2, m - 1) + 1;
      return dp[n][m];
   }
   else
   {
      int a = func(str1, n - 1, str2, m);
      int b = func(str1, n, str2, m - 1);
      dp[n][m] = a > b ? a : b;
      return dp[n][m];
   }
}


int main(void)
{
   dp = new int*[str1.size()];
   for (int i = 0; i < str1.size(); ++i)
   {
      (dp[i]) = new int[str2.size()]();
   }
   cout << func(str1, str1.size() - 1, str2, str2.size() - 1);
   for (int i = 0; i < str1.size(); ++i)
   {
      for (int j = 0; j < str2.size(); ++j)
      {
         cout << dp[i][j] << " ";
      }
      cout << endl;
   }

   return 0;
}

