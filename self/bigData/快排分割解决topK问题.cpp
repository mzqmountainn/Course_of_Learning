//
// Created by mzq on 2026/5/29.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>

//思路：使用快排分割，当pos+1==k时 说明此时前面排好序的序列正好满足前k的条件 返回
//      pos+1>k时 对前面进行快排分割
//      pos+1<k时 同理

int partation(int arr[], int begin, int end)
{
    int base = arr[begin];
    int i = begin;
    int j = end;
    while (i < j)
    {
        while (i < j && arr[i] < base)
        {
            i++;
        }
        if (i < j)
        {
            arr[j] = arr[i];
            j--;
        }
        while (i < j && arr[j] > base)
        {
            j--;
        }
        if (i < j)
        {
            arr[i] = arr[j];
            i++;
        }
    }
    arr[i] = base;
    return i;
}

void selectTopK(int arr[], int begin, int end, int k)
{
    int pos = partation(arr, begin, end);
    if (pos + 1 == k) { return; }
    else if (pos + 1 > k)
    {
        selectTopK(arr, begin, pos - 1, k);
    }
    else
    {
        selectTopK(arr, pos + 1, end, k);
    }
}

int main(void)
{
    srand(time(NULL));
    int arr[100];
    for (int i = 0; i < 100; ++i)
    {
        arr[i] = (rand() % 1000);
    }
    selectTopK(arr, 0, 99, 10);
    for (int i = 0; i < 10; ++i)
    {
        std::cout << arr[i] << " ";
    }
    return 0;
}
