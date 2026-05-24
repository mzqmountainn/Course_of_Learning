//
// Created by 18455 on 2026/5/6.
//
#include <iostream>

using namespace std;

class Queue {
private:
    int *pmQue;
    int cap_;
    int front_;
    int rear_;
public:
    Queue(int size = 10) : cap_(size), front_(0), rear_(0) {
        pmQue = new int[size];
    }
    ~Queue() {
        delete[]pmQue;
        pmQue = nullptr;
    }
private:
    void expand(int size) {
        int *p = new int[size];
        int i = 0;
        int j = front_;
        for (; (j + 1) % cap_ != rear_; j++, i++) {
            p[i] = pmQue[j];
        }
        p[i] = pmQue[j];
        cap_ = size;
        front_ = 0;
        rear_ = i+1;
        delete []pmQue;
        pmQue = p;
    }
public:
    bool empty(void) const {
        return rear_ == front_;
    }
    int front(void) const {
        if (this->empty())
            throw "queue empty!";
        return pmQue[front_];
    }
    int back(void) const {
        if (this->empty())
            throw "queue empty!";
        return pmQue[(rear_-1+cap_)%cap_];
    }
    void push(int val) {
        if ((rear_ + 1) % cap_ == front_)
            expand(2 * cap_);
        pmQue[rear_] = val;
        rear_++;
    }
    void pop(void) {
        if (this->empty())
            throw "queue empty!";
        front_ = (front_ + 1) % cap_;
    }
    int size(void) {
        int result = 0;
        for (int i = front_; i != rear_; (++i) % cap_) {
            result++;
        }
        return result;
    }
};
int main()
{
    int arr[] = { 12,4,56,7,89,31,53,75 };
    Queue que;

    for (int v : arr)
    {
        que.push(v);
    }
    cout << que.size() << endl;
    cout << que.front() << endl;
    cout << que.back() << endl;
//    while (!que.empty()){
//        cout << que.front() << " ";
//        que.pop();
//    }


    que.push(100);
    cout << que.back() << endl;
    cout << que.size() << endl;
    que.push(200);
    cout << que.back() << endl;
    cout << que.size() << endl;
    que.push(300);
    cout << que.back() << endl;
    cout << que.size() << endl;

    cout << que.size() << endl;
    cout << que.front() << endl;
    cout << que.back() << endl;
    cout<<endl;

    while (!que.empty())
    {
        cout << que.front() << " " << que.back() << endl;
        que.pop();
    }
}