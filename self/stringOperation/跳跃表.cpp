//
// Created by mzq on 2026/10/14.
//
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>

class SkipList {
public:
    SkipList() {
        head_ = new headNode(1);
    };

    ~SkipList() {
        for (int i = 0; i < head_->level_; ++i) {
            node *cur = head_->next_;
            while (cur != nullptr) {
                node *temp = cur->next_;
                delete cur;
                cur = temp;
            }
            cur = head_;
            head_ = static_cast<headNode *>(head_->down_);
            delete cur;
        }
    };
    bool find(int val);
    void add(int val);

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

bool SkipList::find(int val) {
    node *pre = head_;
    node *cur = pre->next_;
    for (;;) {
        if (cur->val_ < val) {
            pre = cur;
            cur = cur->next_;
            continue;
        } else if (cur->val_ == val) {
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
    headNode *hNode = new headNode(level);
    hNode->down_ = head_;
    head_ = hNode;
    node **nodeList = new node *[level];
    //先将新创建的节点串在一起
    for (int i = level; i > 0; --i) {
        nodeList[i] = new node(val);
        if (i < level) {
            nodeList[i]->down_ = nodeList[i + 1];
        }
    }
    //插入
    node *pre = head_;
    node *cur = head_->next_;
    for (int i = 0; i < level; ++i) {
        while (cur != nullptr || cur->val_ < val) {
            pre = cur;
            cur = cur->next_;
        }
    }
}
int main(void) {
    return 0;
}
