// 12_快速排序.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 快排分割处理函数
int Partation(int arr[], int l, int r)
{
	// 选择基准数的优化：“三数取中”法   arr[l]   arr[r]   arr[(l+r)/2]  
	// 记录基准数
	int val = arr[l];

	// 一次快排处理   时间：O(n) * O(logn) = O(nlogn)    空间：O(logn) 递归的深度所占用的栈内存
	while (l < r)  
	{
		while (l < r && arr[r] > val)
		{
			r--;
		}

		if (l < r)
		{
			arr[l] = arr[r];
			l++;
		}

		while (l < r && arr[l] < val)
		{
			l++;
		}

		if (l < r)
		{
			arr[r] = arr[l];
			r--;
		}
	}

	// l == r的位置，就是放基准数的位置
	arr[l] = val;
	return l;
}

// 快排的递归接口
void QuickSort(int arr[], int begin, int end)
{
	if (begin >= end) // 快排递归结束的条件
	{
		return;
	}

	// 优化一：当[begin, end]序列的元素个数小到指定数量，采用插入排序
	//if (end - begin <= 50)
	//{
		// InsertSort(arr, begin, end);
		//return;
	//}

	// 在[begin, end]区间的元素做一次快排分割处理
	int pos = Partation(arr, begin, end);

	// 对基准数的左边和右边的序列，再分别进行快排
	QuickSort(arr, begin, pos - 1);
	QuickSort(arr, pos + 1, end);
}

// 快速排序
void QuickSort(int arr[], int size)
{
	return QuickSort(arr, 0, size - 1);
}

int main()
{
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100 + 1;
	}

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	QuickSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}