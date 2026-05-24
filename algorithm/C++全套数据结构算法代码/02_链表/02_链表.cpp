// 02_链表.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 节点类型
struct Node
{
    Node(int data = 0) :data_(data), next_(nullptr) {}
    int data_;
    Node* next_;
};

// 单链表代码实现
class Clink
{
public:
    Clink()
    {
        // 给head_初始化指向头节点
        head_ = new Node();
    }
    ~Clink()
    {
        // 节点的释放
        Node* p = head_;
        while (p != nullptr)
        {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
        head_ = nullptr;
    }

public:
    // 链表尾插法 O(n)   head_:头节点    tail_:尾节点
    void InsertTail(int val)
    {
        // 先找到当前链表的末尾节点
        Node* p = head_;
        while (p->next_ != nullptr)
        {
            p = p->next_;
        }

        // 生成新节点
        Node* node = new Node(val);
        // 把新节点挂在尾节点的后面
        p->next_ = node;
    }
    // 链表的头插法  O(1)
    void InsertHead(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }
    // 链表节点的删除
    void Remove(int val)
    {
        Node* q = head_;
        Node* p = head_->next_;

        while (p != nullptr)
        {
            if (p->data_ == val)
            {
                // 删除一个节点本身的操作是O(1)
                q->next_ = p->next_;
                delete p;
                return;
            }
            else
            {
                q = p;
                p = p->next_;
            }
        }
    }
    // 删除多个节点
    void RemoveAll(int val)
    {
        Node* q = head_;
        Node* p = head_->next_;

        while (p != nullptr)
        {
            if (p->data_ == val)
            {
                q->next_ = p->next_;
                delete p;
                // 对指针p进行重置
                p = q->next_;
            }
            else
            {
                q = p;
                p = p->next_;
            }
        }
    }
    // 搜索 list O(n) 数组的搜索  下表访问/随机访问arr[i]O(1)  搜索O(n)
    bool Find(int val)
    {
        Node* p = head_->next_;
        while (p != nullptr)
        {
            if (p->data_ == val)
            {
                return true;
            }
            else
            {
                p = p->next_;
            }
        }
        return false;
    }
    // 链表打印
    void Show()
    {
        Node* p = head_->next_;
        while (p != nullptr)
        {
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }
private:
    Node* head_; // 指向链表的头节点

    friend void ReverseLink(Clink& link);
    friend bool GetLaskKNode(Clink& link, int k, int& val);
    friend void MergeLink(Clink& link1, Clink& link2);
};

// 单链表逆序
void ReverseLink(Clink &link)
{
    Node* head = link.head_;
    Node* p = head->next_;
    if (p == nullptr)
    {
        return;
    }

    head->next_ = nullptr;

    while (p != nullptr)
    {
        Node* q = p->next_;

        // p指针指向的节点进行头插
        p->next_ = head->next_;
        head->next_ = p;

        p = q;
    }
}

// 求倒数第k个节点的值
bool GetLaskKNode(Clink& link, int k, int& val)
{
    Node* head = link.head_;
    Node* pre = head;
    Node* p = head;

    if (k < 1)
    {
        return false;
    }

    for (int i = 0; i < k; i++)
    {
        p = p->next_;
        if (p == nullptr)
        {
            return false;
        }
    }

    // pre在头节点，p在正数第k个节点
    while (p != nullptr)
    {
        pre = pre->next_;
        p = p->next_;
    }

    val = pre->data_;
    return true;
}

// 合并两个有序的单链表
void MergeLink(Clink& link1, Clink& link2)
{
    Node* p = link1.head_->next_;
    Node* q = link2.head_->next_;
    Node* last = link1.head_;
    link2.head_->next_ = nullptr;

    while (p != nullptr && q != nullptr)
    {
        if (p->data_ < q->data_)
        {
            last->next_ = p;
            p = p->next_;
            last = last->next_;
        }
        else
        {
            last->next_ = q;
            q = q->next_;
            last = last->next_;
        }
    }

    if (p != nullptr)
    {
        last->next_ = p;
    }
    else
    {
        last->next_ = q;
    }
}

// 判断单链表是否存在环，存在返回环的入口节点
bool IsLinkHasCircle(Node *head, int& val)
{
    Node *fast = head;
    Node* slow = head;

    while (fast != nullptr && fast->next_ != nullptr)
    {
        slow = slow->next_;
        fast = fast->next_->next_;

        if (slow == fast)
        {
            // 快慢指针再次遇见，链表存在环
            fast = head;
            while (fast != slow)
            {
                slow = slow->next_;
                fast = fast->next_;
            }
            val = slow->data_;
            return true;
        }
    }
    return false;
}

// 判断两个单链表是否相交，如果相交，返回相交节点的值
bool IsLinkHasMerge(Node* head1, Node* head2, int& val)
{
    int cnt1 = 0, cnt2 = 0;
    Node* p = head1->next_;
    Node* q = head2->next_;

    while (p != nullptr)
    {
        cnt1++;
        p = p->next_;
    }

    while (q != nullptr)
    {
        cnt2++;
        q = q->next_;
    }

    p = head1;
    q = head2;
    if (cnt1 > cnt2)
    {
        // 第一个链表长
        int offset = cnt1 - cnt2;
        while (offset-- > 0)
        {
            p = p->next_;
        }
    }
    else
    {
        // 第二个链表长
        int offset = cnt2 - cnt1;
        while (offset-- > 0)
        {
            q = q->next_;
        }
    }

    while (p != nullptr && q != nullptr)
    {
        if (p == q)
        {
            val = p->data_;
            return true;
        }
        p = p->next_;
        q = q->next_;
    }

    return false;
}

int main()
{
    Node head1;
    Node n1(25), n2(67), n3(32), n4(18);
    head1.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;

    Node head2;
    Node n5(31);
    head2.next_ = &n5;
    n5.next_ = &n1;

    int val;
    if (IsLinkHasMerge(&head1, &head2, val))
    {
        cout << "链表相交，相交节点是：" << val << endl;
    }
}

#if 0
int main()
{
    Node head;

    Node n1(25), n2(67), n3(32), n4(18);
    head.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;
    n4.next_ = &n4;

    int val;
    if (IsLinkHasCircle(&head, val))
    {
        cout << "链表存在环，环的入口节点是：" << val << endl;
    }
}
#endif

#if 0
int main()
{
    int arr[] = {25, 37, 52, 78, 88, 92, 98, 108};
    int brr[] = { 13, 23, 40, 56, 62, 77, 109 };

    Clink link1;
    Clink link2;

    for (int v : arr)
    {
        link1.InsertTail(v);
    }
    
    for (int v : brr)
    {
        link2.InsertTail(v);
    }

    link1.Show();
    link2.Show();

    MergeLink(link1, link2);
    link1.Show();
    link2.Show();
}
#endif

#if 0
int main()
{
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        int val = rand() % 100;
        link.InsertTail(val);
    }
    link.Show();

    ReverseLink(link);
    link.Show();

    int kval;
    int k = 10;
    if (GetLaskKNode(link, k, kval))
    {
        cout << "倒数第" << k << "个节点的值:" << kval << endl;
    }
}
#endif


#if 0
int main()
{
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        int val = rand() % 100;
        link.InsertHead(val);
        cout << val << " ";
    }
    cout << endl;

    link.InsertTail(23);
    link.InsertHead(23);
    link.InsertHead(23);

    link.Show();

    link.RemoveAll(23);
    link.Show();
}
#endif