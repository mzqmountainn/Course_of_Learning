
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。
例如，给定三角形：
[
	 [2],
	[3,4],
   [6,5,7],
  [4,1,8,3]
]
自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。

说明：
如果你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题，那么你的算法会很加分。
*/
int main()
{
	vector<int> v1 = { 2 };
	vector<int> v2 = { 3,4 };
	vector<int> v3 = { 6,5,7 };
	vector<int> v4 = { 4,1,8,3 };
	vector<vector<int>> v = { v1,v2,v3,v4 };

	// 状态：dp[i][j] : 第i行j列元素开始选择数字，的和的最大值
	int **dp = nullptr;
	dp = new int*[v.size()];
	for (int i = 0; i < v.size(); ++i) {
		dp[i] = new int[v4.size()]();
	}

	int n = v.size() - 1;
	for (int i = 0; i < v4.size(); ++i) {
		dp[n][i] = v[n][i];
	}

	for (int i = n - 1; i >= 0; --i) {
		for (int j = 0; j < v[i].size(); ++j) {
			dp[i][j] = std::min(dp[i+1][j], dp[i+1][j+1]) + v[i][j];
		}
	}

	cout << dp[0][0] << endl;

	// 释放dp数组的内存
	for (int i = 0; i < v.size(); ++i) {
		delete[]dp[i];
	}
	delete[]dp;
	return 0;
}