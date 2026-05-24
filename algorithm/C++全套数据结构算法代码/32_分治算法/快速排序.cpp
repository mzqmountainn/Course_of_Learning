#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 快排划分函数，调整基准数
int partation(vector<int> &vec, int i, int j) {
	int val = vec[i]; // 作为基准数
	int l = i;
	int r = j;
	while (l < r) {
		while (l < r && vec[r] >= val) { // 右 - 左  找第一个比val小的
			r--;
		}
		if (l < r) {
			vec[l++] = vec[r];
		}
		while (l < r && vec[l] < val) { // 左 - 右  找第一个比val大的
			l++;
		}
		if (l < r) {
			vec[r--] = vec[l];
		}
	}
	vec[l] = val;  // 放置基准数
	return l; // 返回基准数的下标
}
void quickSort(vector<int> &vec, int i, int j) {
	if (i >= j) {
		return;
	}
	int pos = partation(vec, i, j);
	quickSort(vec, i, pos - 1);
	quickSort(vec, pos + 1, j);
}
int main2()
{
	vector<int> vec;
	for (int i = 0; i < 11; ++i) {
		vec.push_back(rand() % 100);
	}
	
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;

	quickSort(vec, 0, vec.size() - 1);
	for (int v : vec) {
		cout << v << " ";
	}

	cout << endl;

	return 0;
}