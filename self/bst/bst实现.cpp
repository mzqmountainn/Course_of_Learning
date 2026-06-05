//
// Created by mzq on 2026/6/3.
//

#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

template<typename T, typename Comp = less<T> >

class BSTree {
private:
    struct Node {
        T data_;
        Node *leftChild;
        Node *rightChild;
        Node *root;
        Node(T data = T()) : data_(data), leftChild(nullptr), rightChild(nullptr) { ; }
    };

    Node *root_;
    Comp comp_;

public:
    BSTree(Comp c = Comp()) : root_(nullptr), comp_(c) { ; }
    //非递归插入
    void n_insert(T const &val) {
        if (root_ == nullptr) {
            root_ = new Node(val);
            return;
        }
        Node *cur = root_;
        Node *parent = nullptr;
        while (cur != nullptr) {
            //决定是否需要进入左孩子
            if (comp_(val, cur->data_)) {
                parent = cur;
                cur = cur->leftChild;
            } else if (val == cur->data_) {
                return;
            } else if (!comp_(val, cur->data_)) {
                parent = cur;
                cur = cur->rightChild;
            } //判断是否重复
        }
        cur = new Node(val);
        //判断插入左孩子还是右孩子
        if (comp_(val, parent->data_)) {
            parent->leftChild = cur;
        } else {
            parent->rightChild = cur;
        }
        cur = nullptr;
        return;
    }

    void n_remove(T const &val);
    bool n_query(T const &val);
    /*bst树的前序、中序、后续遍历
     *V 当前节点 L左子节点 R右子节点
     *VLR LVR LRV
     */
    void preOrder() {
        cout << "前序遍历:";
        preOrder(root_);
        cout << endl;
    };
    void inOrder() {
        cout << "中序遍历:";
        inOrder(root_);
        cout << endl;
    };
    void postOrder() {
        cout << "后序遍历:";
        postOrder(root_);
        cout << endl;
    };
    //递归实现层级遍历
    void levelOrder(void);
    //递归返回树的高度
    int high(void) {
        return high(root_);
    }
    //递归返回节点数量
    int number(void) {
        return number(root_);
    }

private:
    //递归实现 此处本质为深度优先搜索
    void preOrder(Node *node);
    void inOrder(Node *node);
    void postOrder(Node *node);
    //递归实现返回树的深度
    int high(Node *node);
    //递归实现返回树的深度
    int number(Node *node);
    void levelOrder(Node *node, int level);
};

/*
BST树删除节点
1.没有孩子的节点父节点地址域nullpt
2.有一个孩子孩子写入父节点地址域
3.删除的节点有两个孩子
找待删除节点的前驱节点（或者后继节点），用前驱或者后继节点的值把待删除节点的值覆盖
掉，然后直接删除前驱或者后继节点就可以了
*/
template<typename T, typename Comp>
void BSTree<T, Comp>::n_remove(T const &val) {
    if (root_ == nullptr) {
        return;
    }
    //寻找删除节点
    Node *cur = root_;
    Node *parent = nullptr;
    while (cur != nullptr) {
        if (cur->data_ == val) {
            break;
        } else if (comp_(cur->data_, val)) {
            parent = cur;
            cur = cur->rightChild;
        } else {
            parent = cur;
            cur = cur->leftChild;
        }
    }
    //为空说明找不到要删除的元素 结束
    if (cur == nullptr)
        return;
    Node *target = cur;

    //接下来开始判断是否属于情况3，判断是否有两个孩子
    if (cur->leftChild != nullptr && cur->rightChild != nullptr) {
        //寻找前驱节点
        parent = cur;
        cur = cur->leftChild;
        while (cur->rightChild != nullptr) {
            parent = cur;
            cur = cur->rightChild;
        }
        //将前驱节点的值和要删除的值交换
        target->data_ = cur->data_;
    }
    //进入删除，首先排除特殊情况：要删除的是root 且root左右孩子中只有一个孩子或者没有
    if (parent == nullptr && cur == root_) {
        if (root_->leftChild != nullptr) {
            parent = root_;
            root_ = root_->leftChild;
            delete parent;
            parent = nullptr;
        } else if ((root_->rightChild != nullptr)) {
            parent = root_;
            root_ = root_->rightChild;
            delete parent;
            parent = nullptr;
        } else {
            delete root_;
            root_ = nullptr;
        }
        return;
    }
    //处理正常情况
    if (parent->leftChild == cur) {
        parent->leftChild = (cur->leftChild == nullptr ? cur->rightChild : cur->leftChild);
    } else if (parent->rightChild == cur) {
        parent->rightChild = (cur->leftChild == nullptr ? cur->rightChild : cur->leftChild);
    }
    delete cur;
}

template<typename T, typename Comp>
bool BSTree<T, Comp>::n_query(T const &val) {
    Node *cur = root_;
    while (cur != nullptr) {
        if (cur->data_ == val) {
            return true;
        } else if (comp_(cur->data_, val)) {
            cur = cur->rightChild;
        } else {
            cur = cur->leftChild;
        }
    }
    return false;
}
template<typename T, typename Comp>
void BSTree<T, Comp>::preOrder(Node *node) {
    if (node != nullptr) {
        cout << node->data_ << " ";
        preOrder(node->leftChild);
        preOrder(node->rightChild);
    }
    return;
}
template<typename T, typename Comp>
void BSTree<T, Comp>::inOrder(Node *node) {
    if (node != nullptr) {
        inOrder(node->leftChild);
        cout << node->data_ << " ";
        inOrder(node->rightChild);
    }
    return;
}
template<typename T, typename Comp>
void BSTree<T, Comp>::postOrder(Node *node) {
    if (node != nullptr) {
        postOrder(node->leftChild);
        postOrder(node->rightChild);
        cout << node->data_ << " ";
    }
    return;
}

//递归实现返回树的深度
template<typename T, typename Comp>
int BSTree<T, Comp>::high(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    int left = high(node->leftChild);
    int right = high(node->rightChild);
    return (left >= right) ? left + 1 : right + 1;
}

//递归返回节点个数
template<typename T, typename Comp>
int BSTree<T, Comp>::number(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    int left = number(node->leftChild);
    int right = number(node->rightChild);
    return left + right + 1;
}
//递归进行层级遍历
template<typename T, typename Comp>
void BSTree<T, Comp>::levelOrder(void) {
    int depth = high();
    cout << "层级遍历:";
    for (int i = 0; i < depth; ++i) {
        levelOrder(root_, i);
    }
    cout << endl;
    return;
}
//递归进行层级遍历
template<typename T, typename Comp>
void BSTree<T, Comp>::levelOrder(Node *node, int level) {
    if (node == nullptr)
        return;
    //当到达这一层时 才输出 这样保证了只在第n层输出第n层的节点内容
    if (level == 0) {
        cout << node->data_ << " ";
    }
    levelOrder(node->leftChild, level - 1);
    levelOrder(node->rightChild, level - 1);
    return;
}
int main(void) {
    BSTree<int> test1;
    int arr[] = {5, 4, 6, 2, 6, 7, 4, 99};
    for (auto i: arr) {
        test1.n_insert(i);
    }
    // cout << test1.n_query(7);
    // test1.n_remove(7);
    // cout << test1.n_query(7);
    // cout << test1.n_query(66);
    // cout << test1.n_query(99);

    //测试前中后序遍历问题
    BSTree<int> test2;
    int arrr[] = {58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78};
    for (auto i: arrr) {
        test2.n_insert(i);
    }
    test2.preOrder();
    test2.inOrder();
    test2.postOrder();
    test2.levelOrder();

    return 0;
}
