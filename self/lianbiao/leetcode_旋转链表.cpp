//
// Created by 18455 on 2026/4/23.
//
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
//leetcode 61题
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        ListNode *head_ = head;
        ListNode *p = head;
        ListNode *q = head;
        int k_;
        int total = 1;//求总数
        while (p != nullptr && p->next != nullptr) {
            total++;
            p = p->next;
        }
        k_ = k % total;
        for (int i = 0; i < total - k_ - 1; ++i) {
            q = q->next;
        }
        if (p != nullptr && q != nullptr) {
            p->next = head;
            head = q->next;
            q->next = nullptr;
        }
        return head;
    }
};