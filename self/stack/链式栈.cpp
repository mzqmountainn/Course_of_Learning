//
// Created by 18455 on 2026/4/27.
//
#include <iostream>

using namespace std;

class linkStack {
private:
    struct Node {
        Node(int val = 0) : val_(val), next_(nullptr) {};
        int val_;
        Node *next_;
    };

    Node *head_;
    int size_;
public:
    linkStack() : size_(0) {
        head_ = new Node();
    }
    ~linkStack() {
        Node *p = head_;
        while (p != nullptr) {
            head_ = p->next_;
            delete p;
            p = head_;
        }
    }
public:
    void push(int val) {
        Node *p = new Node(val);
        size_++;
        p->next_ = head_->next_;
        head_->next_ = p;
    }
    int top(void) {
        return head_->next_->val_;
    }
    void pop(void) {
        size_--;
        Node *p = head_->next_;
        if (p == nullptr)
            throw "stack is empty";
        head_->next_ = p->next_;
        delete p;
    }
    bool empty(void){
        return head_->next_== nullptr;
    }
    int size(void){
        return size_;
    }
};
int main(void){
    linkStack test;
    int arr[] = {1, 2, 3, 4,5,6,7,8,9};
    for (int n:arr) {
        test.push(n);
    }
    while (!test.empty()){
        cout<<test.top()<<" ";
        test.pop();
    }
}