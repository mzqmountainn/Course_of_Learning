//
// Created by 18455 on 2026/10/9.
//
#include <iostream>
#include <string>
#include <memory>

using namespace std;

string text = "ABCDCABDEFG";
string pattern = "ABD";

int *nextArr;
int *getNext(string parttern) {
    const int size = parttern.size();
    int *Next = new int[size];

    int k = -1; //公共前后缀的长度
    int j = 0;
    Next[j] = k;
    while (j < parttern.size() - 1) {
        if (k == -1 || parttern[k] == parttern[j]) {
            k++;
            j++;
            if (parttern[j] == parttern[k]) {
                Next[j] = Next[k];
            } else {
                Next[j] = k;
            }
        } else {
            k = Next[k];
        }
    }
    return Next;
}
int KMP(string s, string t) {
    int i = 0;
    int j = 0;

    while (i < s.size() && int(j) < int(t.size())) // Attention:string.size() returns UNSIGNED INT
    {
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else {
            j = nextArr[j];
        }
    }

    if (j == t.size()) // 找到了
    {
        return i - j;
    } else {
        return -1;
    }
}
int main(void) {
    unique_ptr<int> ptr(nextArr);
    string s = "abcabdefabcabc"; //"ABCDCABDEFG";
    string t = "abcabc"; //"ABD";
    nextArr = getNext(t);
    cout << KMP(s, t);
}
