//
// Created by 18455 on 2026/5/5.
//
//leetcode 150题
//https://leetcode.cn/problems/evaluate-reverse-polish-notation/?envType=problem-list-v2&envId=stack

#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int calculate(int left, int right, char sign) {
        switch (sign) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/':
                return left / right;
        }
        throw "no matches!";
    }
    int evalRPN(vector<string> &tokens) {
        stack<int> intStack;
        for (string &str: tokens) {
            if (str.size() == 1 && (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/')) {
                int right = intStack.top();
                intStack.pop();
                int left = intStack.top();
                intStack.pop();
                intStack.push(calculate(left, right, str[0]));
            } else {
                intStack.push(stoi(str));
            }
        }
        return intStack.top();
    }
};