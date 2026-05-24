//
// Created by 18455 on 2026/5/10.
//
#include <iostream>

using namespace std;

int BinarySearch(int arr[], int size, int val) {
    int first = 0;
    int last = size - 1;
    int middle;
    while (first <= last) {
        middle = (int) ((first + last) / 2);
        if (arr[middle] == val)
            return middle;
        else if (arr[middle] > val)
            last = middle - 1;
        else
            first = middle + 1;
    }
    return -1;
}
//二分搜索递归实现
int BinarySearch(int arr[], int i, int j, int val) {
    if (i > j)
        return -1;
    int mid = (i + j) / 2;
    if (arr[mid] == val) {
        return mid;
    } else if (arr[mid] > val) {
        return BinarySearch(arr, i, mid - 1, val);
    } else
        return BinarySearch(arr, mid + 1, j, val);
}

int main(void) {
    int arr[] = {12, 25, 34, 39, 45, 57, 63, 78, 82, 96, 100};
    int size = sizeof arr / sizeof arr[0];
    cout << BinarySearch(arr, size, 39) << endl;
    cout << BinarySearch(arr, size, 45) << endl;
    cout << BinarySearch(arr, size, 12) << endl;
    cout << BinarySearch(arr, size, 64) << endl;
    cout << BinarySearch(arr, 0, size, 39) << endl;
    cout << BinarySearch(arr, 0, size, 45) << endl;
    cout << BinarySearch(arr, 0, size, 12) << endl;
    cout << BinarySearch(arr, 0, size, 64) << endl;
}