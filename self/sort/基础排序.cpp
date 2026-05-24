//
// Created by 18455 on 2026/5/11.
//
#include <iostream>

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//冒泡排序
void BubbleSort(int arr[], int size) {
    bool flag = false;
    for (int i = 0; i < size - 1; ++i) {
        flag = false;
        for (int j = 0; j < size - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                flag = true;
            }

        }
        if (!flag)
            return;
    }
    return;
}
//选择排序
void ChoiceSort(int arr[], int size) {
    int min = 0;
    int k = 0;
    for (int i = 0; i < size; ++i) {
        min = arr[i];
        k = i;
        for (int j = i; j < size; ++j) {
            if (arr[j] < min) {
                min = arr[j];
                k = j;
            }
        }
        if (k != i) {
            int temp = min;
            arr[k] = arr[i];
            arr[i] = min;
        }
    }
    return;
}
// 插入排序算法  时间复杂度: 最坏、平均 O(n^2)  最好：O(n)  空间：O(1)  稳定性：稳定的
void InsertSort(int arr[], int size) {
    for (int i = 1; i < size; ++i) {
        int j = i - 1;
        int val = arr[i];
        for (; j >= 0; --j) {
            if (arr[j] <= val) {
                break;
            }
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = val;
    }
}
//希尔排序
void ShellSort(int arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {


        for (int i = gap; i < size; ++i) {
            int j = i - gap;
            int val = arr[i];
            for (; j >= 0; j -= gap) {
                if (arr[j] <= val) {
                    break;
                }
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = val;
        }
    }
}
int main() {
    int arr[10];
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100 + 1;
    }

    for (int v: arr) {
        cout << v << " ";
    }
    cout << endl;

    //BubbleSort(arr, 10);
    //ChoiceSort(arr, 10);
    //InsertSort(arr, 10);
    ShellSort(arr, 10);

    for (int v: arr) {
        cout << v << " ";
    }
    cout << endl;
}