// 16_高级排序性能测试.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
using namespace std;

// 堆的下沉调整
void siftDown(int arr[], int i, int size)
{
	int val = arr[i];
	while (i < size / 2)
	{
		int child = 2 * i + 1;
		if (child + 1 < size && arr[child + 1] > arr[child])
		{
			child = child + 1;
		}

		if (arr[child] > val)
		{
			arr[i] = arr[child];
			i = child;  // i继续指向它的孩子，继续调整
		}
		else
		{
			break;
		}
	}
	arr[i] = val;
}

// 堆排序
void HeapSort(int arr[], int size)
{
	int n = size - 1;
	// 从第一个非叶子节点
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		siftDown(arr, i, size);
	}

	// 把堆顶元素和末尾元素进行交换，从堆顶开始进行下沉操作
	for (int i = n; i > 0; i--)
	{
		int tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;

		siftDown(arr, 0, i); // 第三个参数，参与调整的元素的个数
	}
}

// 归并过程函数  O(n)
void Merge(int arr[], int l, int m, int r, int *p)
{
	int idx = 0;
	int i = l;
	int j = m + 1;

	while (i <= m && j <= r)
	{
		if (arr[i] <= arr[j])
		{
			p[idx++] = arr[i++];
		}
		else
		{
			p[idx++] = arr[j++];
		}
	}

	while (i <= m)
	{
		p[idx++] = arr[i++];
	}

	while (j <= r)
	{
		p[idx++] = arr[j++];
	}

	// 再把合并好的大段有序的结果，拷贝到原始arr数组[l,r]区间内
	for (i = l, j = 0; i <= r; i++, j++)
	{
		arr[i] = p[j];
	}
}

// 归并排序递归接口
void MergeSort(int arr[], int begin, int end, int *p)
{
	// 递归结束的条件
	if (begin >= end)
	{
		return;
	}

	int mid = (begin + end) / 2;
	// 先递
	MergeSort(arr, begin, mid, p);
	MergeSort(arr, mid + 1, end, p);
	// 再归并  [begin, mid]  [mid+1, end] 把两个小段有序的序列，合并成大段有序的序列
	Merge(arr, begin, mid, end, p);
}

// 归并排序
void MergeSort(int arr[], int size)
{
	int* p = new int[size];  // O(n)
	MergeSort(arr, 0, size - 1, p);
	delete[]p;
}

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

// 希尔排序
void ShellSort(int arr[], int size)
{
	for (int gap = size / 2; gap > 0; gap /= 2) // 100W 19 1000W 24
	{
		for (int i = gap; i < size; i++) // O(n)
		{
			int val = arr[i];
			int j = i - gap;
			for (; j >= 0; j -= gap) // O(n)
			{
				if (arr[j] <= val)
				{
					break;
				}
				arr[j + gap] = arr[j];
			}
			arr[j + gap] = val;
		}
	}
}

int main()
{
	cout << RAND_MAX << endl;

	const int COUNT = 100000000;
	int* arr = new int[COUNT];
	int* brr = new int[COUNT];
	/*int* crr = new int[COUNT];
	int* drr = new int[COUNT];*/

	srand(time(NULL));

	// 0 - 32767    32768 - 32768+32767 
	for (int i = 0; i < COUNT; i++)
	{
		int val = rand() % COUNT;  // 0 - 32767
		arr[i] = val;
	}

	clock_t begin, end;

	memcpy(brr, arr, COUNT * sizeof(int));

	begin = clock();
	QuickSort(brr, COUNT);
	end = clock();
	cout << "QuickSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	memcpy(brr, arr, COUNT * sizeof(int));

	begin = clock();
	MergeSort(brr, COUNT);
	end = clock();
	cout << "MergeSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	memcpy(brr, arr, COUNT * sizeof(int));

	begin = clock();
	ShellSort(brr, COUNT);
	end = clock();
	cout << "ShellSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
	
	memcpy(brr, arr, COUNT * sizeof(int));

	begin = clock();
	HeapSort(brr, COUNT);
	end = clock();
	cout << "HeapSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
}