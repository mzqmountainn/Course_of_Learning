// 08_环形队列.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

// 环形队列   queue  push  pop  front  back  empty size
class Queue
{
public:
    Queue(int size = 10)
        : cap_(size)
        , front_(0)
        , rear_(0)
        , size_(0)
    {
        pQue_ = new int[cap_];
    }
    ~Queue()
    {
        delete[]pQue_;
        pQue_ = nullptr;
    }

public:
    // 入队 O(1)
    void push(int val)
    {
        if ((rear_ + 1) % cap_ == front_)
        {
            expand(2 * cap_);
        }
        pQue_[rear_] = val;
        rear_ = (rear_ + 1) % cap_;
        size_++;
    }
    // 出队 O(1)
    void pop()
    {
        if (front_ == rear_)
            throw "queue is empty!";
        front_ = (front_ + 1) % cap_;
        size_--;
    }
    // 队头元素
    int front() const
    {
        if (front_ == rear_)
            throw "queue is empty!";
        return pQue_[front_];
    }
    // 队尾元素
    int back() const
    {
        if (front_ == rear_)
            throw "queue is empty!";
        return pQue_[(rear_ - 1 + cap_) % cap_];
    }
    // 队空
    bool empty() const
    {
        return front_ == rear_;
    }
    // 队列元素的个数
    int size() const
    {
        // return size;  O(1)
        // 遍历一遍统计队列元素个数 O(n)
        int size = 0;
        for (int i = front_; i != rear_; i = (i + 1) % cap_)
        {
            size++;
        }
        return size;
    }

private:
    // 扩容接口
    void expand(int size)
    {
        int* p = new int[size];
        int i = 0;
        int j = front_;
        for (; j != rear_; i++, j = (j + 1) % cap_)
        {
            p[i] = pQue_[j];
        }
        delete[]pQue_;
        pQue_ = p;
        cap_ = size;
        front_ = 0;
        rear_ = i;
    }

private:
    int* pQue_;
    int cap_;   // 空间容量
    int front_; // 队头
    int rear_;  // 队尾
    int size_;  // 队列元素个数
};

int main()
{
    int arr[] = { 12,4,56,7,89,31,53,75 };
    Queue que;

    for (int v : arr)
    {
        que.push(v);
    }
    
    cout << que.front() << endl;
    cout << que.back() << endl;

    que.push(100);
    que.push(200);
    que.push(300);
    cout << que.front() << endl;
    cout << que.back() << endl;

    while (!que.empty())
    {
        cout << que.front() << " " << que.back() << endl;
        que.pop();
    }
}