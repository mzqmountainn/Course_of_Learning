//
// Created by 18455 on 2026/5/16.
//
#include <iostream>
#include <functional>
#include <stdlib.h>
#include <time.h>

using namespace std;
void ShiftDown(int arr[], int i, int size) {
    //在写堆排序的下沉函数时，通常不建议在 while 循环外预先计算最后一个非叶子节点。最安全且通用的做法是：直接在 while 条件里判断左孩子是否越界。
    //int firstNonLeafNode = (size - 2) / 2;
    int val = arr[i];
    while (i < size / 2) {
        int child = 2 * i + 1;
        if (child + 1 <= size - 1 && arr[child + 1] > arr[child]) {
            child += 1;
        }
        if (val < arr[child]) {
            arr[i] = arr[child];
            i = child;
        } else {
            break;
        }
    }
    arr[i] = val;
}
void HeapSort(int arr[], int size) {
    for (int i = (size - 2) / 2; i >= 0; --i) {
        ShiftDown(arr, i, size);
    }
    //将第一个元素与最后一个元素交换，然后第一个元素下沉,此时忽略最后一个元素，重复，忽略的元素也需要+1
    for (int i = size - 1; i > 0; --i) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        ShiftDown(arr, 0, i);
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

    HeapSort(arr, 10);

    for (int v: arr) {
        cout << v << " ";
    }
    cout << endl;
}