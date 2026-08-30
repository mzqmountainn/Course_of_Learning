//
// Created by 18455 on 2026/8/30.
//
/*
*一个叶子节点就代表了原序列的一种排列的可能
*所有叶子节点总和，就是原序列的全部排列方式
*/
#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>

using namespace std;
int arr[] = {1, 2, 3, 4};
std::vector<int> select;
const int length = sizeof(arr) / sizeof(arr[0]);

void swapa(int arr[], int i, int j) {
    int temp = arr[j];
    arr[j] = arr[i];
    arr[i] = temp;
}
void func(int i, int arr[]) {
    if (i == length) {
        for (int j = 0; j < length; ++j) {
            cout << arr[j] << " ";
        }
        cout << endl;
    } else {
        for (int k = i; k < length; ++k) {
            swapa(arr, i, k);
            func(i + 1, arr);
            swapa(arr, i, k);
        }
    }
}
int main(void) {
    func(0, arr);
    return 0;
}
