//
// Created by 18455 on 2026/11/11.
//
#include <iostream>
#include <algorithm>
#include <list>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <stack>

using namespace std;
const int SIZE = 9;
int tree[SIZE];
int height[SIZE];

int find(int x) {
    while (x != tree[x]) {
        x = tree[x];
    }
    return x;
}
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (height[x] > height[y]) {
            tree[y] = x;
        } else {
            if (height[x] == height[y]) {
                height[y]++;
            }
            tree[x] = y;
        }
        //tree[y] = x;
    }
    return;
}
int main(void) {
    for (int i = 0; i < SIZE; ++i) {
        tree[i] = i;
        height[i] = 1;
    }
    merge(1, 3);
    merge(1, 2);
    merge(5, 4);
    merge(2, 4);
    merge(6, 8);
    merge(8, 7);
    cout << (find(2) == find(4) ? "OK" : "NO") << endl;
}

