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

#if ture
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
#else
string str1 = "helloworld";
string str2 = "hwelloworld";
int** dp = nullptr;
int** path = nullptr;

//非递归解法
//传入的是下标
int LCS(string X, int n, string Y, int m)
{
   for (int i = 1; i <= n + 1; ++i)
   {
      for (int j = 1; j <= m + 1; ++j)
      {
         if (X[i - 1] == Y[j - 1])
         {
            dp[i][j] = 1 + dp[i - 1][j - 1];
            path[i][j] = 1;
         }
         else
         {
            int len1 = dp[i - 1][j];
            int len2 = dp[i][j - 1];
            if (len1 > len2)
            {
               dp[i][j] = len1;
               path[i][j] = 3;
            }
            else
            {
               dp[i][j] = len2;
               path[i][j] = 2;
            }
         }
      }
   }
   return dp[n + 1][m + 1];
}

void backStrace(string str1, int n, int m)
{
   if (n <= 0 || m <= 0)
   {
      return;
   }

   if (path[n][m] == 1)
   {
      // 对应位置的元素是相等的
      backStrace(str1, n - 1, m - 1); // 向对角线递归
      cout << str1[n - 1];
   }
   else
   {
      if (path[n][m] == 2)
      {
         backStrace(str1, n, m - 1); // 向左递归
      }
      else
      {
         // path[n][m] = 3
         backStrace(str1, n - 1, m); // 向上递归
      }
   }
}

int main(void)
{
   // dp是一个n行m列的二维数组
   int n = str1.size();
   int m = str2.size();
   dp = new int*[n + 1]; // n行
   for (int i = 0; i < n + 1; ++i)
   {
      dp[i] = new int[m + 1]; // m列
      for (int j = 0; j < m + 1; ++j)
      {
         // dp[i][j] = -1;
         dp[i][j] = 0;
      }
   }
   path = new int*[n + 1]; // n行
   for (int i = 0; i < n + 1; ++i)
   {
      path[i] = new int[m + 1](); // m列
   }
   //传入的是下标
   int size = LCS(str1, n - 1, str2, m - 1);
   cout << "LCS length:" << size << endl;

   // backStrace(str1, n-1, m-1);
   backStrace(str1, n, m);

   //for (int i = 0; i < n; ++i) {   // 行
   //	for (int j = 0; j < m; ++j) { // 列
   //		cout << path[i][j] << " ";
   //	}
   //	cout << endl;
   //}

   // 释放dp数组内存
   return 0;
   return 0;
}
#endif

