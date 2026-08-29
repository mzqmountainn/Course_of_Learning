//
// Created by mzq on 2026/8/29.
//
//整数选择问题：给定2n个整数，从里面挑选出n个整数，让选择的整数的和，和剩下的整数的和的差最小
#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>
using namespace std;
long long int count = 0;
int arr[] = {
    12, 6, 7, 11, 16, 3, 9, 5, 354, 64, 23, 54, 53, 232, 64, 74, 54, 234, 645, 24, 54, 88, 45, 34, 66, 32, 4, 6, 3, 4,
    23, 65
};
const int length = sizeof(arr) / sizeof(arr[0]);
const int HALF = length / 2;
vector<int> select;
//记录最佳组合
vector<int> best;
int sum = 0;
int MinSum = INT32_MAX;
//未被选择数字之和
int r = 0;

void func(int i) {
    count++;
    if (i == length) {
        int result = abs(sum - r);
        if (result < MinSum) {
            MinSum = result;
            best = select;
        }
    } else {
        if (select.size() < HALF) {
            select.push_back(arr[i]);
            sum += arr[i];
            r -= arr[i];
            func(i + 1);
            //
            select.pop_back();
            sum -= arr[i];
            r += arr[i];
        }
        if (select.size() + (length - i) >= HALF) {
            func(i + 1);
        }
    }
}

int main(void) {
    for (int it: arr) {
        r += it;
    }
    func(0);
    for (auto it: best) {
        cout << it << " ";
    }
    std::cout << std::endl;
    std::cout << "min:" << MinSum << endl;
    cout << "count:" << count;
    return 0;
}
