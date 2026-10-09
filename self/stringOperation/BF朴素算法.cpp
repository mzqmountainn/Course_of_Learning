//
// Created by 18455 on 2026/10/8.
//
#include <iostream>
#include <string>
#include <memory>

using namespace std;

string text = "ABCDCABDEFG";
string pattern = "ABD";

int main(void) {
    int pos = 0;
    int i = 0;
    int j = 0;
    while (i < text.length() && j < pattern.length()) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == pattern.length()) {
        pos = i - j;
    } else {
        pos = -1;
    }
    cout << pos << endl;
    return 0;
}
