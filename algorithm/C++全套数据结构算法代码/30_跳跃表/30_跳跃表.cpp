// 30_跳跃表.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

// 跳跃表SkipList
class SkipList
{
public:
	SkipList()
	{
		head_ = new HeadNode(1);
	}
	~SkipList()
	{
		int level = head_->level_;
		for (int i = 0; i < level; i++)
		{
			Node* cur = head_->next_;
			while (cur != nullptr)
			{
				Node* tmp = cur->next_;
				delete cur;
				cur = tmp;
			}
			cur = head_;
			head_ = static_cast<HeadNode*>(head_->down_);
			delete cur;
		}
	}

public:
	// 搜索数据
	bool find(int data)
	{
		Node* pre = head_;
		Node* cur = pre->next_;

		for (;;)
		{
			if (cur != nullptr)
			{
				if (cur->data_ < data)
				{
					pre = cur;
					cur = cur->next_;
					continue;
				}
				else if (cur->data_ == data)
				{
					return true;
				}
			}

			// cur == nullptr了
			if (pre->down_ == nullptr)
			{
				// pre和cur已经遍历到第一层的末尾了
				break;
			}

			pre = pre->down_;
			cur = pre->next_;
		}
		return false;
	}

	// 添加数据
	void add(int data)
	{
		// 先查找数据是否存在
		if (find(data))
			return;

		// 抛硬币，data数据添加几层
		int level = getLevel();
		if (level > head_->level_)
		{
			// level过大时，SkipList只增长一层
			level = head_->level_ + 1;
			HeadNode* hnode = new HeadNode(level);
			hnode->down_ = head_;
			head_ = hnode;
		}

		// 先创建level层的data节点，修改down指针域
		Node** nodeList = new Node * [level];
		for (int i = level - 1; i >= 0; i--)
		{
			nodeList[i] = new Node(data);
			if (i < level - 1)
			{
				// 上面节点的down指针域，存储下面节点的地址
				nodeList[i]->down_ = nodeList[i + 1];
			}
		}

		Node* head = head_;
		for (int i = head_->level_; i > level; i--)
		{
			head = head->down_;
		}

		// head就指向了要插入节点的链表了
		Node* pre = head;
		Node* cur = pre->next_;

		for (int i = 0; i < level; i++)
		{
			while (cur != nullptr && cur->data_ < data)
			{
				pre = cur;
				cur = cur->next_;
			}

			// 新节点插入到pre和cur的中间
			nodeList[i]->next_ = cur;
			pre->next_ = nodeList[i];

			pre = pre->down_;
			if (pre != nullptr)
				cur = pre->next_;
		}

		delete[]nodeList;
		nodeList = nullptr;
	}

	// 删除数据
	void remove(int data)
	{
		Node* pre = head_;
		Node* cur = pre->next_;

		for (;;)
		{
			if (cur != nullptr)
			{
				if (cur->data_ < data)
				{
					pre = cur;
					cur = cur->next_;
					continue;
				}
				else if (cur->data_ == data)
				{
					// 删除cur指向的节点
					pre->next_ = cur->next_;
					delete cur;
				}
			}

			if (pre->down_ == nullptr)
			{
				break;
			}

			pre = pre->down_;
			// cur == nullptr 当前层没有data节点
			if (head_->next_ == nullptr)
			{
				delete head_;
				head_ = static_cast<HeadNode*>(pre);
			}
			cur = pre->next_;
		}
	}

	// 打印
	void show() const
	{
		Node* head = head_;
		while (head != nullptr)
		{
			Node* cur = head->next_;
			while (cur != nullptr)
			{
				cout << cur->data_ << " ";
				cur = cur->next_;
			}
			cout << endl;
			head = head->down_;
		}
		cout << endl;
	}

private:
	int getLevel() const
	{
		int level = 1;
		while (rand() % 2 == 1)
			level++;
		return level;
	}

private:
	// 普通节点类型
	struct Node
	{
		Node(int data = int())
			: data_(data)
			, next_(nullptr)
			, down_(nullptr)
		{}
		int data_;     // 数据域
		Node* next_;   // 指向同一层后一个节点的指针域
		Node* down_;   // 指向下一层相同节点的指针域
	};

	// 跳跃表的头节点类型
	struct HeadNode : public Node
	{
		HeadNode(int level)
			: level_(level)
		{}
		int level_; // 跳跃表的层数
	};

private:
	HeadNode* head_;   // 指向跳表最上面一层链表的头节点
};

int main()
{
	SkipList list;
	srand(time(nullptr));

	for (int i = 0; i < 20; i++)
	{
		list.add(rand() % 100);
	}

	list.add(50);
	list.show();

	list.remove(50);
	list.show();

	return 0;
}