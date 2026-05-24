//
// Created by 18455 on 2026/4/25.
//

//leetcode 19题
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode *p = head;
        ListNode *q = head;
        for (int i = 0; i < n; ++i) {
            if(q->next== nullptr)
                return head->next;
            q = q->next;
        }
        while (q->next!= nullptr){
            q = q->next;
            p = p->next;
        }
        p->next = p->next->next;
        return head;
    }
};