//
// Created by 18455 on 2026/4/27.
//
#include <iostream>

using namespace std;

class seqStack {
private:
    int *stack_;
    int top_;
    int cap_;
private:
    void expand(int size) {
        int *p = new int[size];
        memcpy(p, stack_, size * sizeof(int));
        delete[]stack_;
        stack_ = p;
    }
public:
    seqStack(int size = 5) : top_(0), cap_(size) {
        stack_ = new int[size];
    }
    ~seqStack() {
        delete[]stack_;
        stack_ = nullptr;
    }
public:
    bool empty(void) const {
        if (top_ == 0)
            return true;
        return false;
    }
    int size(void) const {
        return cap_;
    }
    void push(int val) {
        if (top_ == cap_) {
            expand(2 * cap_);
            cap_ = 2 * cap_;
        }
        stack_[top_++] = val;
    }
    int top(void) {
        if (top_ == 0)
            throw "no stack!";
        return stack_[top_-1];
    }
    void pop(void) {
        if (top_ == 0)
            throw "no stack!";
        top_--;
    }
};
int main(void){
    seqStack test;
    int arr[] = {1, 2, 3, 4,5,6,7,8,9};
    for (int n:arr) {
        test.push(n);
    }
    while (!test.empty()){
        cout<<test.top()<<" ";
        test.pop();
    }
}