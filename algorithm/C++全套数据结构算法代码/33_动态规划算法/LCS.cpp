
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
static int cnt = 0; // 用于代码测试

string str1 = "helloworld";
string str2 = "hlweord";
int **dp = nullptr;
int **path = nullptr; // 记录最长子序列

#if 0
// 递归实现
int LCS(string X, int n, string Y, int m) {
	if (n < 0 || m < 0) {
		return 0;
	}

	if (dp[n][m] >= 0) {  // 查表，查子问题的解是否被求过
		return dp[n][m];
	}

	cnt++; // 分治算法：628次    动态规划：40

	if (X[n] == Y[m]) {
		dp[n][m] = LCS01(X, n - 1, Y, m - 1) + 1;
		path[n][m] = 1;  // n,m  => n-1,m-1  对角线
		return dp[n][m];
	}
	else {
		int len1 = LCS01(X, n, Y, m - 1);
		int len2 = LCS01(X, n - 1, Y, m);
		if (len1 >= len2) {
			dp[n][m] = len1;
			path[n][m] = 2; // n,m => n,m-1  左边
		}
		else {
			dp[n][m] = len2;
			path[n][m] = 3; // n,m => n-1,m   上方
		}
		return dp[n][m];
	}
}
#endif

// 非递归实现
int LCS(string X, int i, string Y, int j) {
	for (int n = 1; n <= i+1; ++n) {
		for (int m = 1; m <= j+1; ++m) {
			if (X[n-1] == Y[m-1]) {
				dp[n][m] = 1 + dp[n - 1][m - 1];  // n==0 m ==0
				path[n][m] = 1;
			}
			else {
				int len1 = dp[n-1][m]; // 上面来
				int len2 = dp[n][m-1]; // 左边来
				if (len1 >= len2) {
					dp[n][m] = len1;
					path[n][m] = 3;
				} 
				else {
					dp[n][m] = len2;
					path[n][m] = 2;
				}
			}
		}
	}
	return dp[i+1][j+1];
}

void backStrace(string str1, int n, int m) {
	if (n <= 0 || m <= 0) {
		return;
	}

	if (path[n][m] == 1) {  // 对应位置的元素是相等的
		backStrace(str1, n - 1, m - 1); // 向对角线递归
		cout << str1[n-1];
	}
	else {
		if (path[n][m] == 2) {
			backStrace(str1, n, m - 1);  // 向左递归
		}
		else {  // path[n][m] = 3
			backStrace(str1, n - 1, m); // 向上递归
		}
	}
}
int main5()
{
	// dp是一个n行m列的二维数组
	int n = str1.size();
	int m = str2.size();
	dp = new int*[n+1];   // n行
	for (int i = 0; i < n+1; ++i) {
		dp[i] = new int[m+1];  // m列
		for (int j = 0; j < m+1; ++j) {
			// dp[i][j] = -1;
			dp[i][j] = 0;
		}
	}
	path = new int*[n+1];   // n行
	for (int i = 0; i < n+1; ++i) {
		path[i] = new int[m+1]();  // m列
	}

	int size = LCS(str1, n-1, str2, m-1);
	cout << "LCS length:" << size << endl;
	cout << "cnt:" << cnt << endl;

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
}