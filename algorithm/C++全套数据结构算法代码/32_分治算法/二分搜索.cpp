// 分治算法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 分治算法思想 - 二分搜索
bool binarySearch(vector<int> &vec, int i, int j, int val) {
	if (i > j) {  // 元素不存在
		return false;
	}

	int mid = (i + j) / 2;
	if (vec[mid] == val) {  // 子问题[i,j] 解是已知的了
		return true;
	} 
	else if (vec[mid] > val) { // 在[i, mid-1]子规模问题中
		return binarySearch(vec, i, mid-1, val);
	}
	else { // 在[mid+1, j]子规模问题中
		return binarySearch(vec, mid + 1, j, val);
	}
}
int main1()
{
	vector<int> vec;
	for (int i = 0; i < 11; ++i) {
		vec.push_back(rand() % 100);
	}
	sort(vec.begin(), vec.end());
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;

	bool result = binarySearch(vec, 0, vec.size() - 1, 34);
	cout << "result:" << result << endl;

	return 0;
}