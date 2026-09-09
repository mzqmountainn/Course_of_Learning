//
// Created by 18455 on 2026/9/9.
//
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

// int weight[] = {8, 6, 4, 2, 5};
// int value[] = {6, 4, 7, 8, 6};
// int capacity = 12;

int weight[] = {1, 2, 3, 4, 5, 60};
int value[] = {10, 20, 30, 50, 50, 1000};
int capacity = 60;
const int length = sizeof(weight) / sizeof(weight[0]);
int **dp = nullptr;
void backStace(void) {
    multimap<int, int> select;
    int index = capacity;
    for (int i = 1; i < length; ++i) {
        if (dp[i][index] != (dp[i + 1][index])) {
            select.insert({weight[i - 1], value[i - 1]});
            index -= weight[i - 1];
        }
    }
    //单独处理最后一行
    if (dp[length][index] > 0) {
        select.insert({weight[length - 1], value[length - 1]});
    }
    cout << endl;
    for (auto it: select) {
        cout << it.first << " " << it.second << "    ";
    }
}

int main(void) {
    dp = new int *[length + 1];
    for (int j = 0; j <= length; ++j) {
        dp[j] = new int[capacity + 1]();
    }
    //先计算最后一个物品
    for (int i = 1; i <= capacity; ++i) {
        if (weight[length - 1] <= i) {
            dp[length][i] = value[length - 1];
        }
    }

    //对后续的物品进行计算
    for (int i = length - 1; i > 0; --i) {
        for (int j = 1; j <= capacity; ++j) {
            if (weight[i - 1] > j) {
                dp[i][j] = dp[i + 1][j];
            } else {
                dp[i][j] = std::max(dp[i + 1][j], value[i - 1] + dp[i + 1][j - weight[i - 1]]);
            }
        }
    }
    for (int i = 1; i <= length; ++i) {
        for (int j = 0; j <= capacity; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    backStace();
    for (int i = 0; i <= length; ++i) {
        delete[] dp[i];
    }
    delete[] dp;
    return 0;
}
