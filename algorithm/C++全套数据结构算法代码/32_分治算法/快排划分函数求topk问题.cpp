#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 快排划分函数，调整基准数
static int partation(vector<int> &vec, int i, int j) {
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

// 找第k大的，  vec.size()-k 小的 下标
int max_select_topk(vector<int> &vec, int i, int j, int k) {
	int pos = partation(vec, i, j); // pos表示基准数的位置
	if (pos == vec.size() - k) { // 基准数的位置和top k的k值相等了
		return pos;
	}
	else if (pos < vec.size() - k) { // topk应该在基准数的右边
		return max_select_topk(vec, pos + 1, j, k);
	}
	else { // topk应该落在基准数的左边
		return max_select_topk(vec, i, pos - 1, k);
	}
}
// 找第k小的，  k-1小的 下标   3
int min_select_topk(vector<int> &vec, int i, int j, int k) {
	int pos = partation(vec, i, j); // pos表示基准数的位置
	if (pos == k-1) { // 基准数的位置和top k的k值相等了
		return pos;
	}
	else if (pos < k-1) { // topk应该在基准数的右边
		return min_select_topk(vec, pos + 1, j, k);
	}
	else { // topk应该落在基准数的左边
		return min_select_topk(vec, i, pos - 1, k);
	}
}
int main3()
{
	vector<int> vec;
	for (int i = 0; i < 20; ++i) {
		vec.push_back(rand() % 100);
	}

	// 求第top 10大的元素
	int pos = max_select_topk(vec, 0, vec.size() - 1, 4);
	cout << "第topk大的:" << vec[pos] << endl;
	cout << "前topk大的:";
	for (int i = pos; i < vec.size(); ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;

	// 找topl小的
	pos = min_select_topk(vec, 0, vec.size() - 1, 4);
	cout << "第topk小的:" << vec[pos] << endl;
	cout << "前topk小的:";
	for (int i = 0; i <= pos; ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;

	sort(vec.begin(), vec.end());
	for (int v : vec) {
		cout << v << " ";
	}

	cout << endl;

	return 0;
}