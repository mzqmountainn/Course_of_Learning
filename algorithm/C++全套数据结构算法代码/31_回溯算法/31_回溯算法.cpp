// 回溯算法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#if 0
/*
子集树代码
*/
void func(int arr[], int i, int length, int x[])
{
	if (i == length)   // 递归结束的条件 StackOverFlow
	{
		for (int j = 0; j < length; ++j)
		{
			if (x[j] == 1)
			{
				cout << arr[j] << " ";   // 1 2 3
			}
		}
		cout << endl;
	}
	else
	{
		x[i] = 1;   // 选择i节点
		func(arr, i + 1, length, x); // 遍历i的左孩子

		x[i] = 0;  // 不选择i节点
		func(arr, i + 1, length, x); // 遍历i的右孩子
	}
}
int main()
{
	int arr[] = { 1,2,3 };   // 1 2 3 12 13 23 ...
	int length = sizeof(arr) / sizeof(arr[0]);
	int x[3] = { 0 };
	func(arr, 0, length, x);
	return 0;
}
#endif

#if 0
/*
整数选择问题：给定一组整数，从里面挑选出一组整数，让选择的整数的和，和剩下的整数的和的差最小
*/
int arr[] = { 12,6,7,11,16,3,8 };
const int length = sizeof(arr) / sizeof(arr[0]);
//int x[length] = { 0 };  // 子集树辅助数组  记录节点走向左孩子还是右孩子，代表i节点被选择&未被选择
//int bestx[length] = { 0 }; // 记录最优解
vector<int> x;
vector<int> bestx;
unsigned int min = 0xFFFFFFFF; // 记录最小的差值
int sum = 0; // 记录所选子集数字的总和
int r = 0; // 记录未选择数字的和

// 生成子集树
void func(int i)
{
	if (i == length)  // 访问到了子集树的一个叶子节点
	{
		// sum   
		int result = abs(sum - r);
		if (result < min)
		{
			min = result;
			// 需要记录一下差值最小的子集
			bestx = x;
		}
	}
	else
	{
		r -= arr[i];
		sum += arr[i];
		x.push_back(arr[i]);
		func(i + 1); // 选择i节点
		sum -= arr[i];
		r += arr[i];

		x.pop_back();
		func(i + 1); // 不选择i节点
	}
}

//// 生成子集树
//void func(int i)
//{
//	if (i == length)  // 访问到了子集树的一个叶子节点
//	{
//		// sum   
//		int result = abs(sum - r);
//		if (result < min)
//		{
//			min = result;
//			// 需要记录一下差值最小的子集
//			for (int j = 0; j < length; ++j)
//			{
//				bestx[j] = x[j];
//			}
//		}
//	}
//	else
//	{
//		r -= arr[i];
//		sum += arr[i];
//		x[i] = 1;
//		func(i + 1); // 选择i节点
//		sum -= arr[i];
//		r += arr[i];
//
//		x[i] = 0;
//		func(i + 1); // 不选择i节点
//	}
//}

int main()
{
	for (int v : arr)
	{
		r += v;
	}
	func(0);
	/*for (int i = 0; i < length; ++i)
	{
		if (bestx[i] == 1)
		{
			cout << arr[i] << " ";
		}
	}*/
	for (int v : bestx)
	{
		cout << v << " ";
	}
	cout << endl;
	cout << "min:" << min << endl;
	return 0;
}
#endif

#if 1
/*
整数选择问题：给定2n个整数，从里面挑选出n个整数，让选择的整数的和，和剩下的整数的和的差最小
*/
int arr[] = { 12,6,7,11,16,3,8,4 };
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int> x;  // 记录子集中选择的元素
vector<int> bestx; // 记录最优解
int sum = 0; // 记录子集中所选数字的和
int r = 0; // 记录未选择数字的和
unsigned int minval = 0xFFFFFFFF; // 记录最小差值
int leftcnt = length; // 记录未处理的数字的个数
int cnt = 0; // 记录遍历的子集的个数，用于测试

void func(int i)
{
	if (i == length)
	{
		// cnt++;
		// 得到子集树的一个解，对应一个叶子节点
		if (x.size() != length / 2)
		{
			return;
		}

		int result = abs(sum - r);
		if (result < minval)
		{
			minval = result;
			bestx = x;
		}
	}
	else
	{
		leftcnt--;   // 表示处理i节点，表示剩余的未处理的元素的个数
		if (x.size() < length / 2) // 剪左树枝，提高算法效率。选择数字的前提：还未选择够n个整数
		{
			sum += arr[i];
			r -= arr[i];
			x.push_back(arr[i]);
			func(i + 1); // 遍历i的左孩子，表示选择i号位元素
			sum -= arr[i];
			r += arr[i];
			x.pop_back();
		}

		// 这里右树枝可不可以剪枝呢？ 已选择的数字的个数 + 未来能选择的所有的数字的个数(i+1,i+2....n) >= n个元素
		if (x.size() + leftcnt >= length / 2)
		{
			func(i + 1); // 遍历i的右孩子，表示不选择i号位元素
		}

		// 当前i节点已处理完成，回溯到其父节点了
		leftcnt++;
	}
}
int main()
{
	for (int v : arr)
	{
		r += v;
	}
	func(0);
	for (int v : bestx)
	{
		cout << v << " ";
	}
	cout << endl;
	cout << "min:" << minval << endl;
	cout << "cnt:" << cnt << endl;
	return 0;
}
#endif

#if 0
/*
挑选数字：有一组整数，请挑选出一组数字，让他们的和等于指定的值，存在解打印，不存在打印
*/
int arr[] = { 4,8,12,16,7,9,3 };
const int length = sizeof(arr) / sizeof(arr[0]);
int number = 18;
vector<int> x; // 记录选择的数字
int sum = 0; // 记录所选择数字的和
int r = 0; // 记录未处理的数字的和                            不要混淆未处理和未选择
void func(int i)
{
	if (i == length)
	{
		if (sum != number)
		{
			return;
		}
		for (int v : x)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		r -= arr[i]; // 处理当前i节点
		if (sum + arr[i] <= number)  // 剪左树枝   已选择的数字的和+即将要选择的数字
		{
			sum += arr[i];
			x.push_back(arr[i]);
			func(i + 1);
			sum -= arr[i];
			x.pop_back();
		}

		if (sum + r >= number) // 剪右树枝   已选择的数字的和+剩余的可以被选择的数字的和(i+1,i+2....n)
		{
			func(i + 1);
		}
		r += arr[i];
	}
}
int main()
{
	for (int v : arr)
	{
		r += v;
	}
	func(0);
	return 0;
}
#endif

#if 0
/*
挑选数字：有一组整数，请挑选出一组数字，让他们的和等于指定的值，存在解打印，不存在打印
*/
int arr[] = { 4,8,12,16,7,9,3,3 };
const int length = sizeof(arr) / sizeof(arr[0]);
int number = 18;
vector<int> vec; // 存放选择的数字
void func(int i, int number)
{
	if (number == 0)
	{
		for (int v : vec)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		// 以当前节点开始，把剩余元素的孩子节点生成
		for (int k = i; k < length; ++k)
		{
			if (number >= arr[k]) // 剩余的元素小于number（待组成的元素值）
			{
				vec.push_back(arr[k]);
				// 当前层遍历到下一层的时候   arr[k] != arr[k-1]
				// 不允许重复选择元素
				func(k + 1, number - arr[k]); // 遍历孩子节点，arr[k]的孩子节点
				// 允许重复选择元素
				//func(k, number - arr[k]);
				vec.pop_back();
			}
		}
	}
}
int main()
{
	func(0, number);
	return 0;
}
#endif

#if 0
/*
0-1背包问题：有一组物品，其重量分别是:w1,w2,...wn，其价值分别是v1,v2,...,vn，现在有一个背包，其容量是C，
问怎么把物品装入背包，能够使背包的价值最大化？
*/
int w[] = { 12,5,8,9,6 };  // 物品的重量
int v[] = { 9,2,4,7,8 };  // 物品的价值
const int length = sizeof(w) / sizeof(w[0]);
vector<int> x; // 选择的物品
vector<int> bestx; // 记录最优选择的物品
int c = 20; // 背包的容量
int cw = 0; // 已选择物品的重量
int cv = 0; // 已选择物品的价值
int bestv = 0; // 记录装入背包的物品最大价值
int r = 0; // 未处理物品的总价值

void func(int i)
{
	if (i == length)
	{
		if (bestv < cv)
		{
			bestv = cv;
			bestx = x;
		}
	}
	else
	{
		r -= v[i];
		if (cw + w[i] <= c) // 已选择物品的重量 + 即将选择的第i号物品的重量
		{
			cw += w[i];
			cv += v[i];
			x.push_back(w[i]);
			func(i + 1);
			cw -= w[i];
			cv -= v[i];
			x.pop_back();
		}

		// bestv   cv + [i+1,i+2.....n]总价值 > bestv
		if (cv + r > bestv)
		{
			func(i + 1);
		}
		r += v[i];
	}
}
int main()
{
	for (int val : v)
	{
		r += val;
	}
	func(0);
	for (int w : bestx)
	{
		cout << w << " ";
	}
	cout << endl;
	cout << "bestv:" << bestv << endl;
	return 0;
}
#endif

#if 0
/*
解空间-排列树代码
*/
void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}
void func(int arr[], int i, int length)
{
	if (i == length)
	{
		for (int j = 0; j < length; ++j)
		{
			cout << arr[j] << " ";
		}
		cout << endl;
	}
	else
	{
		// 生成i节点的所有孩子节点
		for (int k = i; k < length; ++k)
		{
			swap(arr, i, k);
			func(arr, i + 1, length);
			swap(arr, i, k); // 一定要再交换回来
		}
	}
}
int main()
{
	int arr[] = { 1,2,3,4 };
	int length = sizeof(arr) / sizeof(arr[0]);
	func(arr, 0, length);

	return 0;
}
#endif

#if 0
int cnt = 0; // 统计8皇后的排列次数
void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}
bool judge(int ar[], int i)  // i表示当前放置皇后棋子的位置
{
	for (int j = 0; j < i; ++j)
	{
		if (i == j || ar[i] == ar[j] || abs(i - j) == abs(ar[i] - ar[j]))
		{
			return false;
		}
	}
	return true;
}
void func(int ar[], int i, int length)
{
	if (i == length)
	{
		cnt++;
		for (int j = 0; j < length; ++j)
		{
			cout << ar[j] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = i; k < length; ++k)
		{
			swap(ar, i, k);
			if (judge(ar, i)) // 判断第i个位置的元素，是否满足8皇后的条件   0 - i-1
				func(ar, i + 1, length);  // 生成孩子节点，也就是说会生成一系列的排列方式
			swap(ar, i, k);
		}
	}
}
int main()
{
	// 把ar数组的下标当作行，下标对应的元素的值当作列
	int ar[] = { 1,2,3,4,5,6,7,8 };
	int n = 8;
	func(ar, 0, n);
	cout << "cnt:" << cnt << endl;
	return 0;
}
#endif

#if 0
// 另一种实现全排列的代码   满足leetcode刷题测试用例
int ar[] = { 1,2,3 };
const int N = 3;
bool state[N]; // 记录所有元素是否被选择的状态  true：选择了  false：未选择
vector<int> vec;
void func(int i)
{
	if (i == N)
	{
		for (int v : vec)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = 0; k < N; ++k)
		{
			if (!state[k])
			{
				state[k] = true;
				vec.push_back(ar[k]);
				func(i + 1);  // k：表示的是可选择的元素的起始下标     i：表示层数
				vec.pop_back();
				state[k] = false;
			}
		}
	}
}
int main()
{
	func(0);
	return 0;
}
#endif