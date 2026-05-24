//
// Created by 18455 on 2026/5/8.
//
#include <iostream>
#include <queue>
#include <string>
//leetcode 225 https://leetcode.cn/problems/implement-stack-using-queues/description/?envType=problem-list-v2&envId=stack
using namespace std;

class MyStack {
private:
    queue<int> *q1;
    queue<int> *q2;
public:
    MyStack() {
        q1 = new queue<int>;
        q2 = new queue<int>;
    }
    ~MyStack() {
        delete q1;
        delete q2;
        q1 = nullptr;
        q2 = nullptr;
    }

    void push(int x) {
        q1->push(x);
        while (!q2->empty()){
            q1->push(q2->front());
            q2->pop();
        }
        queue<int> *temp = q1;
        q1 = q2;
        q2 = temp;
    }

    int pop() {
        int i =q2->front();
        q2->pop();
        return i;
    }

    int top() {
        int i =q2->front();
        return i;
    }

    bool empty() {
        return q2->empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */