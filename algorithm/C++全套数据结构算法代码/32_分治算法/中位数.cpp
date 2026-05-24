#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// O(logn)对数时间求解中位数
double middleValue(vector<int> &nums1, int length1, vector<int> &nums2, int length2) {
	if (length1 > length2) { // 在短的数组中求解合适的i和j值
		return middleValue(nums2, length2, nums1, length1);
	}

	if (length1 == 0) {
		// 0 0 0 0 0 0 0    (6-1)/2=3   
		int k = (length2 - 1) / 2;
		if (length2 % 2 == 0) {
			return (nums2[k] + nums2[k + 1]) * 1.0 / 2;
		}
		else {
			return nums2[k];
		}
	}

	int i = 0;
	int j = 0;
	int begin = 0;
	int end = length1;
	int k = (length1 + length2 + 1) / 2;    // 7 / 2 = 3   0 0 0 0 0 0 0
	while (begin <= end) {  // 二分搜索的算法思想，对数时间找到i+j = k
		i = (begin + end) / 2; 
		j = k - i;
		if (i > 0 && j < length2 && nums1[i - 1] > nums2[j]) {
			end = i - 1;
		}
		else if (j > 0 && i < length1 && nums2[j - 1] > nums1[i]) {
			begin = i + 1;
		}
		else {
			break; // arr[i-1] < brr[j] && brr[j-1] < arr[i]
		}
	}
	// nums1特别短，而且nums1数组的元素的值都特别大
	int left = 0;
	if (i == 0) {  // 中位数肯定都在num2这个数组当中
		left = nums2[j - 1];
	} 
	else if (j == 0) { // nums2这个数组太短了  中位数肯定都在num1这个数组当中
		left = nums1[i - 1];
	}
	else {
		left = std::max(nums1[i - 1], nums2[j - 1]);
	}
	int right = 0;
	if (i == length1) { // nums1数组元素太少，而且值都特别的小   中位数肯定都在num2这个数组当中
		right = nums2[j];
	}
	else if (j == length2) { //中位数肯定都在num1这个数组当中
		right = nums1[i];
	}
	else {
		right = std::min(nums1[i], nums2[j]);
	}
	// 找到了合适的i和j的值
	if ((length1 + length2) % 2 == 0) { // 偶数长度
		return (left + right)*1.0 / 2;
	}
	else { // 奇数长度
		return left;
	}
}
int main()
{
	vector<int> vec1;
	vector<int> vec2;
	//for (int i = 0; i < 10; ++i) {
	//	vec1.push_back(rand() % 100);
	//}

	for (int i = 0; i < 5; ++i) {
		vec2.push_back(rand() % 100);
	}

	vector<int> vec = vec1;
	for (int v : vec2) {
		vec.push_back(v);
	}
	sort(vec.begin(), vec.end());
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;

	sort(vec1.begin(), vec1.end());
	sort(vec2.begin(), vec2.end());

	double midval = middleValue(vec1, vec1.size(), vec2, vec2.size());
	cout << "midval:" << midval << endl;

	return 0;
}