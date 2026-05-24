//
// Created by 18455 on 2026/5/13.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
int Partation(int arr[], int begin, int end) {
    //int base = arr[(int) ((begin + end) / 2)];//注意！如果此处要进行改进，下面代码也需要改进，否则会出现重复数字
    int base = arr[begin];
    while (begin < end) { // test
        while (begin < end && arr[end] > base) {
            end--;
        }
        if (begin < end) {
            arr[begin] = arr[end];
            begin++;
        }
        while (begin < end && arr[begin] < base) {
            begin++;
        }
        if (begin < end) {
            arr[end] = arr[begin];
            end--;
        }
    }
    arr[end] = base;
    return end;

}
void QuickSort(int arr[], int begin, int end) {
    if (begin >= end)
        return;
    int pos = Partation(arr, begin, end);
    QuickSort(arr, begin, pos - 1);
    QuickSort(arr, pos + 1, end);
}
void QuickSort(int arr[], int size) {
    QuickSort(arr, 0, size - 1);
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
    QuickSort(arr, 10);

    for (int v: arr) {
        cout << v << " ";
    }
    cout << endl;
}
