//
// Created by 18455 on 2026/8/31.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
std::vector<int> arr = {41, 52, 34, 20, 79, 53, 24, 53, 66, 88};
int partition(vector<int> &vec, int left, int right) {
    int val = vec[left];
    while (left < right) {
        while (left < right && vec[right] > val) {
            right--;
        }
        if (left < right) {
            vec[left] = vec[right];
            left++;
        }
        while (left < right && vec[left] < val) {
            left++;
        }
        if (left < right) {
            vec[right] = vec[left];
            right--;
        }
    }
    vec[left] = val;
    return left;
}
void quickSort(vector<int> &vec, int left, int right) {
    if (left >= right) {
        return;
    }
    int pos = partition(vec, left, right);
    quickSort(vec, left, pos - 1);
    quickSort(vec, pos + 1, right);
}
void quickSort(vector<int> &vec) {
    quickSort(vec, 0, vec.size() - 1);
}
int main(void) {
    quickSort(arr);
    for (auto it: arr) {
        cout << it << " ";
    }
    return 0;
}
