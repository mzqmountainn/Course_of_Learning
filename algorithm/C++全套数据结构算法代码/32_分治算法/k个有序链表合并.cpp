#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* init_link(initializer_list<int> list) {
	ListNode *head = nullptr;
	ListNode *p = nullptr;
	for (int v : list) {
		if (head == nullptr) {
			head = new ListNode(v);
			p = head;
		}
		else
		{
			p->next = new ListNode(v);
			p = p->next;
		}
	}
	return head;
}

ListNode* mergeTwoLink(ListNode *p1, ListNode *p2) {
	ListNode *head = nullptr;
	if (p1 == nullptr) {
		return p2;
	}
	if (p2 == nullptr) {
		return p1;
	}
	if (p1->val > p2->val) {
		head = p2;
		p2 = p2->next;
	}
	else {
		head = p1;
		p1 = p1->next;
	}
	ListNode *p = head;
	while (p1 != nullptr && p2 != nullptr) {
		if (p1->val > p2->val) {
			p->next = p2;
			p = p2;
			p2 = p2->next;
		}
		else {
			p->next = p1;
			p = p1;
			p1 = p1->next;
		}
	}
	if (p1 != nullptr) {
		p->next = p1;
	}
	if (p2 != nullptr) {
		p->next = p2;
	}
	return head;
}
ListNode* mergeLink(vector<ListNode*> &vlink, int i, int j) {
	if (i >= j) { // 子问题划分到只剩下一个链表了
		return vlink[i];
	}

	int mid = (i + j) / 2;
	ListNode *left = mergeLink(vlink, i, mid);
	ListNode *right = mergeLink(vlink, mid + 1, j);
	return mergeTwoLink(left, right); // 归结成合并两个有序链表
}
int main5()
{
	ListNode *p1 = init_link({ 3, 6, 8 });  // {}
	ListNode *p2 = init_link({ 2, 4 });
	ListNode *p3 = init_link({ 1, 5, 9 });
	ListNode *p4 = init_link({ 0, 7 });
	ListNode *p5 = init_link({ 10 });
	vector<ListNode*> vlink;
	vlink.push_back(p1);
	vlink.push_back(p2);
	vlink.push_back(p3);
	vlink.push_back(p4);
	vlink.push_back(p5);
	ListNode *p = mergeLink(vlink, 0, vlink.size()-1);
	for (ListNode *c = p; c != nullptr; c = c->next) {
		cout << c->val << " ";
	}
	cout << endl;

	return 0;
}