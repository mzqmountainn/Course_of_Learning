//
// Created by 18455 on 2026/4/26.
//
#include <iostream>

/*
 *约瑟夫环问题
 *约瑟夫环是一个数学的应用问题：已知n个人（以编号1，2，3...n分别表示）围坐在一张圆桌周围，从
 *编号为k的人开始报数，数到m的那个人出列，它的下一个人又从1开始报数，数到m的那个人又出列，
 *依此规律重复下去，直到圆桌周围的人全部出列，输出人的出列顺序。
 */

using namespace std;

struct Node {
    Node(int val = 0) : val_(val), next_(nullptr) {};
    int val_;
    Node *next_;
};

void Joseph(Node *head, int k, int m) {
    Node *p = head;
    Node *q = head;//q紧随p，做删除辅助指针
    while (q->next_!=head){
        q= q->next_;
    }
    for (int i = 0; i < k - 1; ++i) {
        p = p->next_;
        q = q->next_;
    }
    while (1){
        if(p==q)
            return;
        for (int i = 0; i < m-1; ++i) {
            p = p->next_;
            q = q->next_;
        }
        cout<<p->val_<<" ";
        q->next_ = p->next_;
        delete p;
        p = q->next_;
    }
}
int main(void) {
    Node* head = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);
    Node* n8 = new Node(8);

    head->next_ = n2;
    n2->next_ = n3;
    n3->next_ = n4;
    n4->next_ = n5;
    n5->next_ = n6;
    n6->next_ = n7;
    n7->next_ = n8;
    n8->next_ = head;

    Joseph(head, 1, 5);
    return 0;
}