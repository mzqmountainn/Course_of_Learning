//
// Created by 18455 on 2026/8/30.
//
#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>
int count = 0;
int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
const int length = sizeof(arr) / sizeof(arr[0]);

using namespace std;

void swapMy(int arr[], int i, int j) {
    int temp = arr[j];
    arr[j] = arr[i];
    arr[i] = temp;
}
bool judge(int i) {
    for (int j = 0; j < i; ++j) {
        if (arr[i] == arr[j] || abs(i - j) == abs(arr[i] - arr[j]) || i == j) {
            return false;
        }
    }
    return true;
}
void func(int i) {
    if (i == length) {
        count++;
        for (int arr1: arr) {
            cout << arr1 << " ";
        }
        cout << endl;
    } else {
        for (int k = i; k < length; ++k) {
            swapMy(arr, i, k);
            if (judge(i)) {
                func(i + 1);
            }
            swapMy(arr, i, k);
        }
    }
}

int main(void) {
    func(0);
    cout << endl << count;
    return 0;
}
