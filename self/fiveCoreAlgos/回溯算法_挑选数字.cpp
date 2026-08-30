//
// Created by mzq on 2026/8/29.
//
//
// Created by mzq on 2026/8/27.
//
//挑选数字：有一组整数，请挑选出一组数字，让他们的和等于指定的值，存在解打印，不存在打印
#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>

//第一种方法
#if 0
using namespace std;
int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
const int sumTarget = 10;
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int> select;
vector<vector<int> > results;
int sum = 0;
//待处理的总和
int r = 0;


void func(int i) {
    if (i == length) {
        if (sum == sumTarget) {
            results.push_back(select);
            for (auto it: select) {
                cout << it << " ";
            }
            cout << endl;
        }
    } else {
        if (sum + arr[i] <= sumTarget) {
            select.push_back(arr[i]);
            r -= arr[i];
            sum += arr[i];
            func(i + 1);
            sum -= arr[i];
            r += arr[i];
            select.pop_back();
        }
        if (sum + r >= sumTarget) {
            func(i + 1);
        }
    };
}

int main(void) {
    for (auto it: arr) {
        r += it;
    }
    func(0);
    return 0;
}


#else
using namespace std;
#include <vector>
long long int count = 0;
int arr[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50
};
const int sumTarget = 52;
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int> select;
vector<vector<int> > results;
int sum = 0;
//待处理的总和
int r = 0;
void func(int i) {
    count++;
    //注意 此方法的判断条件不再是length
    if (sum == sumTarget) {
        results.push_back(select);
        for (auto it: select) {
            cout << it << " ";
        }
        cout << endl;
    } else {
        for (int k = i; k < length; k++) {
            if (sumTarget - sum >= arr[k]) {
                {
                    sum += arr[k];
                    select.push_back(arr[k]);
                    func(k + 1);
                    sum -= arr[k];
                    select.pop_back();
                }
            }
        }
    }
}

int main(void) {
    for (auto it: arr) {
        r += it;
    }
    func(0);
    cout << endl;
    cout << count;
    return 0;
}

#endif
