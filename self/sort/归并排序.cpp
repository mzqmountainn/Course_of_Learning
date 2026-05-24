//
// Created by 18455 on 2026/5/14.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void MergeSort(int arr[], int begin, int end) {
    if (begin >= end)
        return;
    int mid = (begin + end) / 2;
    MergeSort(arr, begin, mid);
    MergeSort(arr, mid + 1, end);

    int *p = new int[end - begin + 1];
    int k = 0;
    int i = begin, j = mid + 1;
    for (; i <= mid && j <= end;) {
        if (arr[i] < arr[j]) {
            p[k] = arr[i];
            i++;
        } else {
            p[k] = arr[j];
            j++;
        }
        k++;
    }
    while (i <= mid) {
        p[k] = arr[i];
        i++;
        k++;
    }
    while (j <= end) {
        p[k] = arr[j];
        j++;
        k++;
    }
    for (int l = begin, count = 0; l <= end; ++l, count++) {
        arr[l] = p[count];
    }
    delete[]p;
}

void MergeSort(int arr[], int size) {
    MergeSort(arr, 0, size - 1);
}
int main() {
    //int arr[10];
    srand(time(NULL));

//    for (int i = 0; i < 10; i++) {
//        arr[i] = rand() % 100 + 1;
//    }
    int arr[] = {34, 6, 12, 64, 7, 43, 778, 22, 33, 444};

    for (int v: arr) {
        cout << v << " ";
    }
    cout << endl;
    MergeSort(arr, 10);

    for (int v: arr) {
        cout << v << " ";
    }
    cout << endl;
}