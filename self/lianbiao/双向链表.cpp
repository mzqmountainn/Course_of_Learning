//
// Created by 18455 on 2026/4/26.
//
#include <iostream>

using namespace std;

struct Node {
    Node(int val = 0) : val_(val), next_(nullptr), pre_(nullptr) {};
    int val_;
    Node *next_;
    Node *pre_;
};

class doubleLink {
private:
    Node *head_;
public:
    doubleLink() {
        head_ = new Node();
    }
    ~doubleLink() {
        Node *p = head_;
        while (p != nullptr) {
            p = p->next_;
            delete head_;
            head_ = p;
        }
        delete p;
    }
    void insertHead(int val) {
        Node *p = new Node(val);
        p->pre_ = head_;
        p->next_ = head_->next_;
        if (head_->next_ != nullptr)
            head_->next_->pre_ = p;
        head_->next_ = p;
    }
    void insertTail(int val) {
        Node *p = new Node(val);
        Node *temp = head_;
        while (temp->next_ != nullptr) {
            temp = temp->next_;
        }
        temp->next_ = p;
        p->pre_ = temp;
    }
    bool find(int val) {
        Node *p = head_->next_;
        while (p != nullptr) {
            if (p->val_ == val) {
                return true;
            }
            p = p->next_;
        }
        return false;
    }
    void remove(int val) {
        Node *p = head_;
        while (p != nullptr) {
            if (p->val_ == val) {
                p->pre_->next_ = p->next_;
                if (p->next_ != nullptr)
                    p->next_->pre_ = p->pre_;
                return;
            }
            p = p->next_;
        }
    }
    void show(void){
        Node*p = head_->next_;
        while (p!= nullptr){
            cout<<p->val_<<" ";
            p=p->next_;
        }
    }


};

int main(void) {
    doubleLink test;
    test.insertHead(2);
    test.insertHead(1);
    test.insertTail(3);
    test.show();
    test.remove(2);
    test.show();
    return 0;
}