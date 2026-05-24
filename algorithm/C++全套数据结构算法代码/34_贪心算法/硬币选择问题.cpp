// 贪心算法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
using namespace std;

/*
1,3,5分的硬币，现在给定一个价值c：11，问组成价值c需要的最少的硬币的数量？？？
*/
int main1()
{
	int arr[] = { 1,3,5 };
	int length = sizeof(arr) / sizeof(arr[0]);
	int c = 11;

	sort(arr, arr + length, [](int a, int b)->bool {return a > b; });

	int idx = 0;  // 5 3 1
	int cnt = 0; // 记录硬币的个数
	while (c > 0) {
		if (c >= arr[idx]) {
			c -= arr[idx];
			cnt++;
		}
		else {
			idx++;
		}
	}

	cout << cnt << endl;

	return 0;
}