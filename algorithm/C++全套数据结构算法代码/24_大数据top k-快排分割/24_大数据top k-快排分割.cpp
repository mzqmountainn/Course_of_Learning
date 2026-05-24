// 24_大数据top k-快排分割.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

// 快排分割函数
int Partation(int arr[], int begin, int end)
{
    int val = arr[begin];
    int i = begin;
    int j = end;

    while (i < j)
    {
        while(i < j&& arr[j] < val)
            j--;

        if (i < j)
        {
            arr[i] = arr[j];
            i++;
        }

        while (i < j && arr[i] > val)
            i++;

        if (i < j)
        {
            arr[j] = arr[i];
            j--;
        }
    }

    arr[i] = val;
    return i;
}

// 求top k的函数
void SelectTopK(int arr[], int begin, int end, int k)
{
    int pos = Partation(arr, begin, end);
    if (pos == k - 1)
    {
        return;
    }
    else if (pos > k - 1)
    {
        SelectTopK(arr, begin, pos - 1, k);
    }
    else
    {
        SelectTopK(arr, pos + 1, end, k);
    }
}

int main()
{
    int arr[] = { 64, 45, 52, 80, 66, 68, 0, 2, 18, 75 };
    int size = sizeof arr / sizeof arr[0];

    // 求值最小的前3个元素
    int k = 3;
    SelectTopK(arr, 0, size - 1, k);

    for (int i = 0; i < k; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}