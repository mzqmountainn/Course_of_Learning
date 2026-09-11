//
// Created by 18455 on 2026/9/11.
//
#include <iostream>
#include <algorithm>
using namespace std;

/*
1,3,5分的硬币，现在给定一个价值c：11，问组成价值c需要的最少的硬币的数量？？？
*/
int main() {
    int c = 17;
    int coins[] = {1, 3, 5};
    int num_coins = sizeof(coins) / sizeof(coins[0]);
    int min_coins = 0;
    sort(coins, coins + num_coins, greater<int>());
    while (c > 0) {
        for (int i = 0; i < num_coins; ++i) {
            if (c >= coins[i]) {
                c -= coins[i];
                min_coins++;
                break;
            }
        }
    }
    cout << min_coins << endl;
    return 0;
}
