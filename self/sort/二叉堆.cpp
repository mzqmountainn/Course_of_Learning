//
// Created by 18455 on 2026/5/15.
//

#include <iostream>
#include <functional>
#include <stdlib.h>
#include <time.h>

using namespace std;

// 优先级队列实现   priority_queue(vector)  push pop top empty size
class PriorityQueue {
public:
    using Comp = function<bool(int, int)>;
    PriorityQueue(int cap = 20, Comp compMethod = greater<int>()) : cap_(cap), comp_(compMethod), size_(0) {
        mQue_ = new int[cap];
    }
    PriorityQueue(Comp compMethod) : cap_(20), comp_(compMethod), size_(0) {
        mQue_ = new int[cap_];
    }
    ~PriorityQueue() {
        delete[]mQue_;
        mQue_ = nullptr;
    }
    int size(void) const {
        return size_;
    }
    int empty(void) const {
        return (size_ == 0);
    }
    int top(void) const {
        if (size_ == 0)
            throw "PriorityQueue is empty!";
        return mQue_[0];
    }
    void push(int val) {
        //expand
        if (size_ == cap_) {
            int *p = new int[2 * cap_];
            memcpy(p, mQue_, cap_ * sizeof(int));
            delete[]mQue_;
            mQue_ = p;
            cap_ *= 2;
        }
        if (size_ == 0) {
            mQue_[0] = val;
            size_++;
            return;
        }
        size_++;
        //堆上浮
        int father;
        int i = size_ - 1;
        for (; i > 0; i = father) {
            father = (i - 1) / 2;
            if (comp_(val, mQue_[father])) {
                mQue_[i] = mQue_[father];
            } else {
                // i = father;
                break;
            }
        }
        mQue_[i] = val;

    }
    void pop(void) {
        if (size_ == 1) {
            size_--;
            return;
        }
        int i = 0;
        //堆下沉
        while (i < (size_ - 1) / 2) {
            int child = 2 * i + 1;
            if (child + 1 <= size_ - 1 && comp_(mQue_[child + 1], mQue_[child]))
                child = child + 1;
            if (comp_(mQue_[child], mQue_[size_ - 1])) {
                mQue_[i] = mQue_[child];
                i = child;
            } else {
                break;
            }
        }
        mQue_[i] = mQue_[size_ - 1];
        size_--;

    }

private:
    int *mQue_;
    int cap_;
    int size_;
    Comp comp_;

};

int main() {
    PriorityQueue que; // 基于大根堆实现的优先级队列

    // 基于小根堆实现的优先级队列
    //PriorityQueue que([](int a, int b) {return a < b; });
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        que.push(rand() % 100);
    }

    while (!que.empty()) {
        cout << que.top() << " ";
        que.pop();
    }
    cout << endl;
}