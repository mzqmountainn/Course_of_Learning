//
// Created by 18455 on 2026/4/26.
//
#include <iostream>

using namespace std;

struct Node {
    Node(int val = 0) : val_(val), next_(nullptr) {};
    int val_;
    Node *next_;
};

class Clink {
private:
    Node *head_;
    Node *tail_;
public:
    Clink() {
        head_ = new Node();
        head_->next_ = head_;
        tail_ = head_;
    }
    ~Clink() {
        Node *p = head_;
        p = p->next_;
        while (p != head_) {
            head_->next_ = p->next_;
            delete p;
            p = head_->next_;
        }
        delete head_;
    }
public:
    void insertTail(int val) {
        Node *p = new Node(val);
        tail_->next_ = p;
        tail_ = p;
        p->next_ = head_;
    }
    void insertHead(int val) {
        Node *p = new Node(val);
        if (head_->next_ == head_) {
            tail_ = p;
        }
        p->next_ = head_->next_;
        head_->next_ = p;
        if (head_->next_ == head_) {
            tail_ = p;
        }
    }
    void show(void) {
        Node *p = head_->next_;
        while (p != head_) {
            cout << p->val_ << " ";
            p = p->next_;
        }
        cout<<endl;
    }
    void remove(int val) {
        Node *p = head_;
        Node *q = head_->next_;
        while (q!=head_){
            if(q->val_==val){
                p->next_ = q->next_;
                delete q;
                //判断删除的是否为最后一个节点
                if(p->next_==head_)
                    tail_ = p;
                return;
            } else{
                p = p->next_;
                q = q->next_;
            }
        }
    }
    bool find(int val){
        Node*p = head_->next_;
        while (p!=head_){
            if(p->val_==val)
                return true;
            p = p->next_;
        }
        return false;
    }
};

int main(void) {
    Clink test;
    test.insertHead(1);
    test.insertHead(2);
    test.insertTail(3);
    test.insertTail(4);
    test.insertHead(2);
    test.show();
    test.remove(4);
    test.show();
    test.insertTail(6);
    test.show();
    cout<<test.find(6);
    cout<<test.find(7);
    return 0;
}