//
// Created by 18455 on 2026/5/21.
//
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

int main(void) {
    // 模拟问题，vector中放原始的数据
    vector<int> vec;
    srand(time(NULL));
    for (int i = 0; i < 10000; i++) {
        vec.push_back(rand() % 10000);
    }
    //Q1:
    // 找第一个出现重复的数字
    // 找所有重复出现的数字unordered_multiset
#if 0
    unordered_set<int> s1;
    for (auto num: vec) {
        auto it = s1.find(num);
        if (it == s1.end()) {
            s1.insert(num);
        } else {
            cout << num << endl;
            break;
        }
    }
#endif
#if 0
    //Q2
    // 统计重复数字以及出现的次数
    unordered_map<int, int> m1;
    for (auto num: vec) {
        auto it = m1.find(num);
        if (it == m1.end()) {
            m1.emplace(num, 1);
        } else {
            it->second++;
        }
    }
    for (auto pair: m1) {
        if (pair.second > 1) {
            cout << "key: " << pair.first << "time: " << pair.second << endl;
        }

    }
#endif
    //Q3
    string src = "jjhfgiyuhrtytrs";
    // 让你找出来第一个没有重复出现过的字符
    unordered_map<char, int> m1;
    for (auto str: src) {
        m1[str]++;
    }
    for (auto str: src) {
        if (m1[str] == 1) {
            cout << str;
            return 0;
        }
    }

}