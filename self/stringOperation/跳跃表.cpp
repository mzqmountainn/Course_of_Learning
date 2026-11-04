//
// Created by mzq on 2026/10/14.
//
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class SkipList {
public:
    SkipList() {
        head_ = new headNode(1);
    };

    ~SkipList() {
        while (head_ != nullptr) {
            node *cur = head_->next_;

            while (cur != nullptr) {
                node *temp = cur->next_;
                delete cur;
                cur = temp;
            }

            headNode *temp = head_;
            head_ = static_cast<headNode *>(head_->down_);
            delete temp;
        }
    }
    bool find(int val);
    void add(int val);
    // 打印
    void show() const;
    void remove(int val);

private:
    int getLevel(void) {
        int level = 1;
        while (rand() % 2 == 1) {
            level++;
        }
        if (level >= head_->level_ + 1) {
            level = head_->level_ + 1;
        }
        return level;
    }

private:
    struct node {
        node *down_;
        node *next_;
        int val_;

        node(int val = int()) : val_(val), down_(nullptr), next_(nullptr) {
        };
    };

    struct headNode : public node {
        int level_;

        headNode(int level) : level_(level) {
        };
    };

    headNode *head_;
};

// 打印
void SkipList::show() const {
    node *head = head_;
    while (head != nullptr) {
        node *cur = head->next_;
        while (cur != nullptr) {
            cout << cur->val_ << " ";
            cur = cur->next_;
        }
        cout << endl;
        head = head->down_;
    }
    cout << endl;
}

bool SkipList::find(int val) {
    node *pre = head_;
    node *cur = pre->next_;
    for (;;) {
        if (cur != nullptr && cur->val_ < val) {
            pre = cur;
            cur = cur->next_;
            continue;
        } else if (cur != nullptr && cur->val_ == val) {
            return true;
        }
        if (pre->down_ == nullptr) {
            break;
        }
        pre = pre->down_;
        cur = pre->next_;
    }
    return false;
}
void SkipList::add(int val) {
    if (find(val))
        return;
    int level = getLevel();
    //如果增加层数 需要新建一个头（新建一层）
    if (level > head_->level_) {
        headNode *hNode = new headNode(level);
        hNode->down_ = head_;
        head_ = hNode;
    }
    node **nodeList = new node *[level];
    //先将新创建的节点串在一起
    for (int i = level - 1; i >= 0; --i) {
        nodeList[i] = new node(val);
        if (i < level - 1) {
            nodeList[i]->down_ = nodeList[i + 1];
        }
    }
    //插入
    node *pre = head_;
    node *cur = head_->next_;

    int totalLevel = head_->level_;

    for (int i = 0; i < totalLevel; ++i) {
        // 寻找当前层的插入位置
        while (cur != nullptr && cur->val_ < val) {
            pre = cur;
            cur = cur->next_;
        }

        // 只在最下面的 level 层插入
        if (i >= totalLevel - level) {
            int index = i - (totalLevel - level);

            nodeList[index]->next_ = cur;
            pre->next_ = nodeList[index];
        }

        // 下降到下一层
        if (i < totalLevel - 1) {
            pre = pre->down_;
            cur = pre->next_;
        }
    }
    delete []nodeList;
}

void SkipList::remove(int val) {
    node *pre = head_;
    node *cur = head_->next_;

    while (1) {
        if (cur != nullptr) {
            if (cur->val_ < val) {
                pre = cur;
                cur = cur->next_;
                continue;
            } else if (cur->val_ == val) {
                pre->next_ = cur->next_;
                delete cur;
            }
        }

        // 先完成所有层的删除
        if (pre->down_ == nullptr) {
            break;
        }

        pre = pre->down_;
        cur = pre->next_;
    }

    // 最后统一删除顶部空层
    while (head_->level_ > 1 &&
           head_->next_ == nullptr) {
        headNode *temp = head_;
        head_ = static_cast<headNode *>(head_->down_);
        delete temp;
    }
}
int main(void) {
    SkipList list;
    // list.add(3);
    // list.add(4);
    // cout << list.find(2);
    // list.show();
    srand(time(nullptr));

    for (int i = 0; i < 20; i++) {
        list.add(rand() % 100);
    }
    list.show();
    for (int i = 80; i < 91; ++i) {
        list.remove(i);
    }
    list.show();
    return 0;
}
