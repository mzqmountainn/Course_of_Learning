//
// Created by 18455 on 2026/5/6.
//
#include <iostream>
#include <stack>
#include <string>
//leetcode 232  https://leetcode.cn/problems/implement-queue-using-stacks/?envType=problem-list-v2&envId=stack
using namespace std;


/*
 * 还有一种复杂度更低的方法，是将s1中导入到s2后，不重复导回s1，而是在s2全部出完后，再将s1导入s2，实现均摊o（1）
 */
class MyQueue {
public:
    stack<int> a;
    stack<int> b;
    MyQueue() {

    }

    void push(int x) {
        a.push(x);
    }

    int pop() {
        while (!a.empty()){
            b.push(a.top());
            a.pop();
        }
        int result = b.top();
        b.pop();
        while (!b.empty()){
            a.push(b.top());
            b.pop();
        }
        return result;
    }

    int peek() {
        while (!a.empty()){
            b.push(a.top());
            a.pop();
        }
        int result = b.top();
        //b.pop();
        while (!b.empty()){
            a.push(b.top());
            b.pop();
        }
        return result;
    }

    bool empty() {
        return a.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */