//
// Created by 18455 on 2026/4/22.
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
    friend void reverse(Clink &link);//类头插法实现链表逆序
    friend bool findLastNode(Clink &link, int k, int &val);//查找倒数第k个节点
    friend void mergeLink(Clink &link1, Clink &link2);//合并两个有序链表
public:
    Clink() {
        head_ = new Node();
    }
    ~Clink() {
        Node *p = head_;
        while (p!= nullptr){
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }
    //o(n)尾插
    void insertTail(int val) {
        Node *p;
        p = head_;
        while (p->next_ != nullptr) {
            p = p->next_;
        }
        p->next_ = new Node(val);
    }
    void insertHead(int val) {
        Node *temp = new Node(val);
        temp->next_ = head_->next_;
        head_->next_ = temp;
    }
    void show(void) {
        Node *p = head_->next_;
        while (p != nullptr) {
            cout << p->val_ << " ";
            p = p->next_;
        }
    }
    void remove(int val) {
        Node *p = head_->next_;
        Node *q = head_;
        while (p != nullptr) {
            if (p->val_ == val) {
                if (p->next_ != nullptr) {
                    q->next_ = p->next_;
                } else {
                    q->next_ = nullptr;
                }
                delete p;
                p = q->next_;
            }
            if (p != nullptr) {
                p = p->next_;
                q = q->next_;
            }
        }
    }
};

void reverse(Clink &link) {

    //特殊情况判断
    if (link.head_->next_ == nullptr) {
        return;
    }
    Node *p = link.head_->next_;
    Node *q;
    link.head_->next_ = nullptr;
    while (p != nullptr) {
        q = p->next_;
        // p->next_ = link.head_->next_;


        p->next_ = link.head_->next_;
        link.head_->next_ = p;
        //p->next_ = nullptr;

        p = q;
    }

}

/*
 * 双指针寻找倒数第k个节点
 * 思路：p先走到整数第k个，然后pre与p一起移动，当p指向null时，pre为查找元素
 */
bool findLastNode(Clink &link, int k, int &val) {
    if (k < 1) {
        return false;
    }
    Node *p, *pre;
    p = link.head_->next_;
    pre = link.head_->next_;
    for (int i = 0; i < k; ++i) {
        p = p->next_;
        if (p == nullptr)
            return false;

    }
    while (p != nullptr) {
        p = p->next_;
        pre = pre->next_;
    }
    val = pre->val_;
    return true;

}
void mergeLink(Clink &link1, Clink &link2) {
    Node *p = link1.head_->next_;
    Node *q = link2.head_->next_;
    Node *last = link1.head_;
    link2.head_->next_ = nullptr;

    while (p != nullptr && q != nullptr) {
        if ((p->val_) < (q->val_)) {
            last->next_ = p;
            p = p->next_;
            last = last->next_;
        } else {
            last->next_ = q;
            q = q->next_;
            last = last->next_;
        }
    }
    if (p != nullptr) {
        last->next_ = p;
    } else {
        last->next_ = q;
    }
}

/*
 * 快慢指针判断链表是否有环并且找出环入口
 * 思路：需要画图来理解x,y,a的关系，推导发现x=a，所以最后fast和slow一起走
 */
bool isLinkHasCircle(Node *src, int &val) {
    Node *fast = src;
    Node *slow = src;
    while (fast != nullptr && fast->next_ != nullptr) {
        fast = fast->next_->next_;
        slow = slow->next_;
        if (slow == fast) {
            slow = src;
            while (fast != slow) {
                fast = fast->next_;
                slow = slow->next_;
            }
            val = fast->val_;
            return true;
        }
    }
    return false;
}
/*
 * 判断链表是否相交
 * 使用双指针，思路与判断是否为环形链表类似
 */
bool isLinkHasMerge(Node *link1, Node *link2, int &val) {
    Node *p = link1;
    Node *q = link2;
    int a = 0;
    int b = 0;
    while (p->next_ != nullptr) {
        a++;
        p = p->next_;
    }
    while (q->next_ != nullptr) {
        b++;
        q = q->next_;
    }
    if (q != p)
        return false;
    p = link1;
    q = link2;
    if (a - b >= 0) {
        int k = a - b;
        for (int i = 0; i < k; ++i) {
            p = p->next_;
        }
        while (p != q) {
            p = p->next_;
            q = q->next_;
        }
        val = p->val_;
    } else {
        int k = b - a;
        for (int i = 0; i < k; ++i) {
            q = q->next_;
        }
        while (p != q) {
            p = p->next_;
            q = q->next_;
        }
        val = p->val_;
    }
    return true;
}
int main(void) {
    Clink test;
    int val = 114514;
    test.insertTail(2);
    test.insertTail(4);
    test.insertTail(3);
    test.insertTail(4);
    test.show();
    cout << endl;
    test.insertHead(1);
    test.show();
    cout << endl;
    test.remove(4);
    test.show();
    cout << endl;
    reverse(test);
    test.show();
    cout << endl;
    findLastNode(test, 1, val);
    cout << val;
    cout << "merge test" << endl;
    Clink merge1, merge2;
    int arr[] = {4, 6, 9, 16, 88};
    int brr[] = {1, 5, 17, 99, 999, 99999};
    for (int n: arr) {
        merge1.insertTail(n);
    }
    for (int n: brr) {
        merge2.insertTail(n);
    }
    mergeLink(merge1, merge2);
    merge1.show();
    cout << endl;
    //构建环链表
    Node circleHead(0), circle1(1), circle2(2), circle3(3), circle4(4), circle5(5);
    circleHead.next_ = &circle1;
    circle1.next_ = &circle2;
    circle2.next_ = &circle3;
    circle3.next_ = &circle4;
    circle4.next_ = &circle5;
    //circle5.next_ = &circle4;
    cout << isLinkHasCircle(&circleHead, val);
    cout << val;
    cout << endl;
    //构建循环列表
    Node MergeHead1(0), MergeHead2(0), Merge1(1), Merge2(2), Merge3(3), Merge4(4), Merge5(5), Merge6(88);
    MergeHead1.next_ = &Merge1;
    Merge1.next_ = &Merge2;
    Merge2.next_ = &Merge3;
    Merge3.next_ = &Merge4;
    Merge4.next_ = &Merge5;
    MergeHead2.next_ = &Merge6;
    Merge6.next_ = &Merge2;
    cout << isLinkHasMerge(&MergeHead1, &MergeHead2, val);
    cout << val;
    return 0;
}