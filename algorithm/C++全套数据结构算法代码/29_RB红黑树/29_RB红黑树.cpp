// RB.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

// 红黑树代码
template<typename T>
class RBTree
{
public:
	RBTree() :root_(nullptr) {}
	// 插入操作
	void insert(const T& val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}

		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ > val)
			{
				parent = cur;
				cur = cur->left_;
			}
			else if (cur->data_ < val)
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				return;
			}
		}

		// 设置当前节点的parent和颜色
		Node* node = new Node(val, parent, nullptr, nullptr, RED);
		if (parent->data_ > val)
		{
			parent->left_ = node;
		}
		else
		{
			parent->right_ = node;
		}

		// 如果新插入的红色节点，父节点也是红色，不满足红黑树性质，进行插入调整操作
		if (RED == color(parent))
		{
			fixAfterInsert(node);
		}
	}
	// 删除操作
	void remove(const T& val)
	{
		if (root_ == nullptr)
		{
			return;
		}

		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ > val)
			{
				cur = cur->left_;
			}
			else if (cur->data_ < val)
			{
				cur = cur->right_;
			}
			else
			{
				break;
			}
		}

		// 没找到val节点返回
		if (cur == nullptr)
		{
			return;
		}

		// 删除前驱节点 情况三
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre; // cur指向前驱节点
		}

		// 删除cur指向的节点  情况一和二
		Node* child = cur->left_; // 让child指向不为空的孩子
		if (child == nullptr)
		{
			child = cur->right_;
		}

		// left right parent
		if (child != nullptr)
		{
			child->parent_ = cur->parent_;
			if (cur->parent_ == nullptr)
			{
				// root_ -> cur_
				root_ = child;
			}
			else
			{
				if (cur->parent_->left_ == cur)
				{
					cur->parent_->left_ = child;
				}
				else
				{
					cur->parent_->right_ = child;
				}
			}

			Color c = color(cur);
			delete cur;

			if (c == BLACK) // 删除的是黑色节点，要进行删除调整操作
			{
				fixAfterRemove(child);
			}
		}
		else
		{
			// child == nullptr
			if (cur->parent_ == nullptr)
			{
				delete cur;
				root_ = nullptr;
				return;
			}
			else
			{
				// 删除的cur就是叶子节点
				if (color(cur) == BLACK)
				{
					fixAfterRemove(cur);
				}

				if (cur->parent_->left_ == cur)
				{
					cur->parent_->left_ = nullptr;
				}
				else
				{
					cur->parent_->right_ = nullptr;
				}

				delete cur;
			}
		}
	}
private:
	// 节点的颜色
	enum Color
	{
		BLACK,
		RED
	};
	// 节点类型
	struct Node
	{
		Node(T data = T(), Node* parent = nullptr,
			Node* left = nullptr, Node* right = nullptr,
			Color color = BLACK)
			:data_(data)
			, left_(left)
			, right_(right)
			, parent_(parent)
			, color_(color)
		{}
		T data_;
		Node* left_;
		Node* right_;
		Node* parent_; // 指向当前节点的父节点
		Color color_;  // 节点的颜色
	};

	// 返回节点的颜色
	Color color(Node* node)
	{
		return node == nullptr ? BLACK : node->color_;
	}
	// 设置节点颜色
	void setColor(Node* node, Color color)
	{
		node->color_ = color;
	}
	// 返回节点的左孩子
	Node* left(Node* node)
	{
		return node->left_;
	}
	// 返回节点的右孩子
	Node* right(Node* node)
	{
		return node->right_;
	}
	// 返回节点的父亲
	Node* parent(Node* node)
	{
		return node->parent_;
	}

	// 左旋转
	void leftRotate(Node* node)
	{
		Node* child = node->right_;
		child->parent_ = node->parent_;
		if (node->parent_ == nullptr)
		{
			// node本身就是root节点
			root_ = child;
		}
		else
		{
			if (node->parent_->left_ == node)
			{
				// node在父节点的左孩子
				node->parent_->left_ = child;
			}
			else
			{
				// node在父节点的右孩子
				node->parent_->right_ = child;
			}
		}

		node->right_ = child->left_;
		if (child->left_ != nullptr)
		{
			child->left_->parent_ = node;
		}

		child->left_ = node;
		node->parent_ = child;
	}
	// 右旋转
	void rightRotate(Node* node)
	{
		Node* child = node->left_;
		child->parent_ = node->parent_;
		if (node->parent_ == nullptr)
		{
			// node原来就是root节点
			root_ = child;
		}
		else
		{
			if (node->parent_->left_ == node)
			{
				// node在父节点的左边
				node->parent_->left_ = child;
			}
			else
			{
				// node在父节点的右边
				node->parent_->right_ = child;
			}
		}

		node->left_ = child->right_;
		if (child->right_ != nullptr)
		{
			child->right_->parent_ = node;
		}

		child->right_ = node;
		node->parent_ = child;
	}
	// 红黑树的插入调整操作
	void fixAfterInsert(Node* node)
	{
		// 如果当前红色节点的父节点也是红色，继续调整
		while (color(parent(node)) == RED)
		{
			if (left(parent(parent(node))) == parent(node))
			{
				// 插入的节点在左子树当中
				Node* uncle = right(parent(parent(node)));
				if (RED == color(uncle)) // 情况一
				{
					setColor(parent(node), BLACK);
					setColor(uncle, BLACK);
					setColor(parent(parent(node)), RED);
					node = parent(parent(node)); // 继续调整
				}
				else
				{
					// 先处理情况三
					if (right(parent(node)) == node)
					{
						node = parent(node);
						leftRotate(node);
					}

					// 统一处理情况二
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					rightRotate(parent(parent(node)));
					break; // 调整已经完成
				}
			}
			else
			{
				// 插入的节点在右子树当中
				Node* uncle = left(parent(parent(node)));
				if (RED == color(uncle)) // 情况一
				{
					setColor(parent(node), BLACK);
					setColor(uncle, BLACK);
					setColor(parent(parent(node)), RED);
					node = parent(parent(node)); // 继续调整
				}
				else
				{
					// 先处理情况三
					if (left(parent(node)) == node)
					{
						node = parent(node);
						rightRotate(node);
					}

					// 统一处理情况二
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					leftRotate(parent(parent(node)));
					break; // 调整已经完成
				}
			}
		}

		// 此处强制root为黑色节点
		setColor(root_, BLACK);
	}
	// 红黑树的删除调整操作
	void fixAfterRemove(Node* node)
	{
		while (node != root_ && color(node) == BLACK)
		{
			if (left(parent(node)) == node)
			{
				// 删除的黑色节点在左子树
				Node* brother = right(parent(node));
				if (color(brother) == RED) // 情况四
				{
					setColor(parent(node), RED);
					setColor(brother, BLACK);
					leftRotate(parent(node));
					brother = right(parent(node));
				}

				if (color(left(brother)) == BLACK
					&& color(right(brother)) == BLACK) // 情况三
				{
					setColor(brother, RED);
					node = parent(node);
				}
				else
				{
					if (color(right(brother)) != RED) // 情况二
					{
						setColor(brother, RED);
						setColor(left(brother), BLACK);
						rightRotate(brother);
						brother = right(parent(node));
					}

					// 归结到情况一
					setColor(brother, color(parent(node)));
					setColor(parent(node), BLACK);
					setColor(right(brother), BLACK);
					leftRotate(parent(node));
					break;
				}
			}
			else
			{
				// 删除的黑色节点在右子树
				Node* brother = left(parent(node));
				if (color(brother) == RED) // 情况四
				{
					setColor(parent(node), RED);
					setColor(brother, BLACK);
					rightRotate(parent(node));
					brother = left(parent(node));
				}

				if (color(left(brother)) == BLACK
					&& color(right(brother)) == BLACK) // 情况三
				{
					setColor(brother, RED);
					node = parent(node);
				}
				else
				{
					if (color(left(brother)) != RED) // 情况二
					{
						setColor(brother, RED);
						setColor(right(brother), BLACK);
						leftRotate(brother);
						brother = left(parent(node));
					}

					// 归结到情况一
					setColor(brother, color(parent(node)));
					setColor(parent(node), BLACK);
					setColor(left(brother), BLACK);
					rightRotate(parent(node));
					break;
				}
			}
		}

		// 如果发现node指向的节点是红色，直接涂成黑色，调整结束
		setColor(node, BLACK);
	}

	// 指向红黑树的根节点
	Node* root_;
};

int main()
{
	RBTree<int> rb;
	for (int i = 1; i <= 10; ++i)
	{
		rb.insert(i);
	}

	rb.remove(9);
	rb.remove(10);
	rb.remove(5);
	rb.remove(3);

	return 0;
}