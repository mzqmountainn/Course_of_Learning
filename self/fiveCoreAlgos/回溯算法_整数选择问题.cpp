//
// Created by mzq on 2026/8/27.
//
//整数选择问题：给定一组整数，从里面挑选出一组整数，让选择的整数的和，和剩下的整数的和的差最小
#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>

int arr[] = {
    12, 6, 7, 11, 16, 3, 9, 5,
};
const int length = sizeof(arr) / sizeof(arr[0]);
//子集树辅助数组
int x[length] = {0};
//记录最佳组合
int xBest[length] = {0};
int sum = 0;
int MinSum = INT32_MAX;
//未被选择数字之和
int r = 0;

void func(int i) {
    if (i == length) {
        int result = abs(sum - r);
        if (result < MinSum) {
            MinSum = result;
            for (int i = 0; i < length; ++i) {
                xBest[i] = x[i];
            }
        }
    } else {
        x[i] += 1;
        sum += arr[i];
        r -= arr[i];
        func(i + 1);
        //
        x[i] -= 1;
        sum -= arr[i];
        r += arr[i];
        func(i + 1);
    }
}

int main(void) {
    for (int it: arr) {
        r += it;
    }
    func(0);
    for (int i = 0; i < length; ++i) {
        if (xBest[i] == 1) {
            std::cout << arr[i] << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "min:" << MinSum;
    return 0;
}
