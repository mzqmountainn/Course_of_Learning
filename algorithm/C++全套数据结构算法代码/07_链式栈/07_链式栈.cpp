// 07_链式栈.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <stack>
using namespace std;

// 比较符号优先级的
bool Priority(char ch, char topch)
{
	if ((ch == '*' || ch == '/') && (topch == '+' || topch == '-'))
		return true;
	if (topch == '(' && ch != ')')
		return true;
	return false;
}

// 中缀表达式 => 后缀表达式
string MiddleToEndExpr(string expr)
{
	string result;
	stack<char> s;

	for (char ch : expr)
	{
		if (ch >= '0' && ch <= '9')
		{
			result.push_back(ch);
		}
		else
		{
			for (;;)
			{
				// 处理符号了
				if (s.empty() || ch == '(')
				{
					s.push(ch);
					break;
				}

				// 比较当前符号ch和栈顶符号top的优先级
				char topch = s.top();
				// Priority:true ch > topch   false ch <= topch
				if (Priority(ch, topch))
				{
					s.push(ch);
					break;
				}
				else
				{
					s.pop();
					if (topch == '(') // 如果遇见)，一直出栈，直到(
						break;
					result.push_back(topch);
				}
			}
		}
	}

	// 如果符号栈还存留符号，直接输出到后缀表达式里面     + /
	while (!s.empty())
	{
		result.push_back(s.top());
		s.pop();
	}

	return result;
}

int main()
{
	cout << MiddleToEndExpr("(1+2)*(3+4)") << endl;
	cout << MiddleToEndExpr("2+(4+6)/2+6/3") << endl;
	cout << MiddleToEndExpr("2+6/(4-2)+(4+6)/2") << endl;
}

#if 0
// 链式栈
class LinkStack
{
public:
	LinkStack(): size_(0)
	{
		head_ = new Node;
	}
	~LinkStack()
	{
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}

public:
	// 入栈 O(1)   把链表头节点后面，第一个有效节点的位置，当作栈顶位置
	void push(int val)
	{
		// head_ -> 1
		// head_ -> 2 -> 1
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		size_++;
	}
	// 出栈 O(1)
	void pop()
	{
		if (head_->next_ == nullptr)
			throw "stack is empty!";
		Node* p = head_->next_;
		head_->next_ = p->next_;
		delete p;
		size_--;
	}
	// 获取栈顶元素
	int top() const
	{
		if (head_->next_ == nullptr)
			throw "stack is empty!";
		return head_->next_->data_;
	}
	// 判空
	bool empty() const
	{
		return head_->next_ == nullptr;
	}
	// 返回栈元素个数   遍历一遍链表，记录节点个数O(n)    想达到O(1)
	int size() const
	{
		return size_;
	}

private:
	struct Node
	{
		Node(int data = 0) : data_(data), next_(nullptr) {}
		int data_;
		Node* next_;
	};

	Node* head_;
	int size_;
};

int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	LinkStack s;

	for (int v : arr)
	{
		s.push(v);
	}

	cout << s.size() << endl;

	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;

	cout << s.size() << endl;
}
#endif