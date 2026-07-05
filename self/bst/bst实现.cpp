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

/*  层序遍历和深度遍历 使用栈
 *  广度遍历 使用队列
 */

using namespace std;

template <typename T, typename Comp = less<T>>

class BSTree
{
    //友元测试函数
public:
    friend void test01();

private:
    struct Node
    {
        T data_;
        Node* leftChild;
        Node* rightChild;
        Node* root;
        Node(T data = T()) : data_(data), leftChild(nullptr), rightChild(nullptr) { ; }
    };

    Node* root_;
    Comp comp_;

public:
    BSTree(Comp c = Comp()) : root_(nullptr), comp_(c) { ; }
    //通过层级遍历进行析构
    ~BSTree()
    {
        queue<Node*> queueForClear;
        if (root_ == nullptr)
        {
            return;
        }
        queueForClear.push(root_);
        while (!queueForClear.empty())
        {
            Node* now = queueForClear.front();
            queueForClear.pop();
            if (now->leftChild != nullptr)
            {
                queueForClear.push(now->leftChild);
            }
            if (now->rightChild != nullptr)
            {
                queueForClear.push(now->rightChild);
            }
            delete now;
        }
    }

    //非递归插入
    void n_insert(T const& val)
    {
        if (root_ == nullptr)
        {
            root_ = new Node(val);
            return;
        }
        Node* cur = root_;
        Node* parent = nullptr;
        while (cur != nullptr)
        {
            //决定是否需要进入左孩子
            if (comp_(val, cur->data_))
            {
                parent = cur;
                cur = cur->leftChild;
            }
            else if (val == cur->data_)
            {
                return;
            }
            else if (!comp_(val, cur->data_))
            {
                parent = cur;
                cur = cur->rightChild;
            } //判断是否重复
        }
        cur = new Node(val);
        //判断插入左孩子还是右孩子
        if (comp_(val, parent->data_))
        {
            parent->leftChild = cur;
        }
        else
        {
            parent->rightChild = cur;
        }
        cur = nullptr;
        return;
    }

    void n_remove(T const& val);
    bool n_query(T const& val);
    /*bst树的前序、中序、后续遍历
     *V 当前节点 L左子节点 R右子节点
     *VLR LVR LRV
     */
    void preOrder()
    {
        cout << "前序遍历:";
        preOrder(root_);
        cout << endl;
    };

    void n_preOrder(void)
    {
        stack<Node*> nodeStack;
        cout << "前序遍历（非递归）";
        if (root_ == nullptr)
        {
            return;
        }
        nodeStack.push(root_);
        while (!nodeStack.empty())
        {
            Node* now = nodeStack.top();
            nodeStack.pop();
            cout << now->data_ << " ";
            //先入栈右孩子再入栈左孩子
            if (now->rightChild != nullptr)
            {
                nodeStack.push(now->rightChild);
            }
            if (now->leftChild != nullptr)
            {
                nodeStack.push(now->leftChild);
            }
        }
        cout << endl;
    }

    void inOrder()
    {
        cout << "中序遍历:";
        inOrder(root_);
        cout << endl;
    };

    /*非递归实现中序遍历
     *思路：先将左边的节点全部入栈，然后出栈后输出元素，然后将右节点入栈
     *如果右节点有左子节点 重复入栈操作
     */
    void n_inOrder(void)
    {
        if (root_ == nullptr)
        {
            return;
        }
        Node* cur = root_;
        stack<Node*> nodeStack;
        cout << "中序遍历（非递归） ";
        //nodeStack.push(cur);
        while (cur != nullptr || !nodeStack.empty())
        {
            if (cur != nullptr)
            {
                nodeStack.push(cur);
                cur = cur->leftChild;
            }
            else
            {
                Node* now = nodeStack.top();
                nodeStack.pop();
                cout << now->data_ << " ";
                cur = now->rightChild;
            }
        }
        cout << endl;
    }

    void postOrder()
    {
        cout << "后序遍历:";
        postOrder(root_);
        cout << endl;
    };
    /*
     *非递归后序遍历
     *思路：后续遍历为LRV 倒过来为VRL 与前序遍历VLR相似 只需要调整左右孩子入栈顺序即可
     *需要使用第二个栈 来使最后的结果反向输出
     */
    void n_postOrder(void)
    {
        if (root_ == nullptr)
        {
            return;
        }
        stack<Node*> s1;
        stack<Node*> s2;
        s1.push(root_);
        cout << "后序遍历（非递归） ";
        while (!s1.empty())
        {
            Node* now = s1.top();
            s1.pop();
            s2.push(now);
            if (now->leftChild != nullptr)
            {
                s1.push(now->leftChild);
            }
            if (now->rightChild != nullptr)
            {
                s1.push(now->rightChild);
            }
        }
        while (!s2.empty())
        {
            Node* now = s2.top();
            s2.pop();
            cout << now->data_ << " ";
        }
        cout << endl;
    }

    //递归实现层级遍历
    void levelOrder(void);

    //非递归实现层级遍历
    void n_levelOrder(void)
    {
        if (root_ == nullptr)
        {
            return;
        }
        queue<Node*> queForleverOrder;
        queForleverOrder.push(root_);
        cout << "层序遍历（非递归）";
        while (!queForleverOrder.empty())
        {
            Node* now = queForleverOrder.front();
            queForleverOrder.pop();
            cout << now->data_ << " ";
            //输出自己之后 将左右孩子入队头
            if (now->leftChild != nullptr)
            {
                queForleverOrder.push(now->leftChild);
            }
            if (now->rightChild != nullptr)
            {
                queForleverOrder.push(now->rightChild);
            }
        }
        cout << endl;
    }

    //递归返回树的高度
    int high(void)
    {
        return high(root_);
    }

    //递归返回节点数量
    int number(void)
    {
        return number(root_);
    }

    //递归实现插入元素
    void insert(const T& val)
    {
        root_ = insert(root_, val);
    }

    //递归查询元素
    bool query(const T& val)
    {
        return nullptr != query(root_, val);
    }

    void remove(const T& val)
    {
        root_ = remove(root_, val);
    }

    //查找区间内的值 public api
    void findValues(vector<T>& vec, int left, int right)
    {
        findValues(root_, vec, left, right);
    }

    //判断是否为bst树
    bool isBSTree(void)
    {
        Node* pre = nullptr;
        return isBSTree(root_, pre);
    }

private
:
    //递归实现 此处本质为深度优先搜索
    void preOrder(Node* node);
    void inOrder(Node* node);
    void postOrder(Node* node);
    //递归实现返回树的深度
    int high(Node* node);
    //递归实现返回树的深度
    int number(Node* node);
    void levelOrder(Node* node, int level);
    Node* insert(Node* node, const T& val);
    Node* query(Node* node, const T& val);
    Node* remove(Node* node, const T& val);
    //查找区间内的值
    void findValues(Node* node, vector<T>& vec, int left, int right);
    bool isBSTree(Node* node, Node* pre);
};

/*
BST树删除节点
1.没有孩子的节点父节点地址域nullpt
2.有一个孩子孩子写入父节点地址域
3.删除的节点有两个孩子
找待删除节点的前驱节点（或者后继节点），用前驱或者后继节点的值把待删除节点的值覆盖
掉，然后直接删除前驱或者后继节点就可以了
*/
template <typename T, typename Comp>
void BSTree<T, Comp>::n_remove(T const& val)
{
    if (root_ == nullptr)
    {
        return;
    }
    //寻找删除节点
    Node* cur = root_;
    Node* parent = nullptr;
    while (cur != nullptr)
    {
        if (cur->data_ == val)
        {
            break;
        }
        else if (comp_(cur->data_, val))
        {
            parent = cur;
            cur = cur->rightChild;
        }
        else
        {
            parent = cur;
            cur = cur->leftChild;
        }
    }
    //为空说明找不到要删除的元素 结束
    if (cur == nullptr)
        return;
    Node* target = cur;

    //接下来开始判断是否属于情况3，判断是否有两个孩子
    if (cur->leftChild != nullptr && cur->rightChild != nullptr)
    {
        //寻找前驱节点
        parent = cur;
        cur = cur->leftChild;
        while (cur->rightChild != nullptr)
        {
            parent = cur;
            cur = cur->rightChild;
        }
        //将前驱节点的值和要删除的值交换
        target->data_ = cur->data_;
    }
    //进入删除，首先排除特殊情况：要删除的是root 且root左右孩子中只有一个孩子或者没有
    if (parent == nullptr && cur == root_)
    {
        if (root_->leftChild != nullptr)
        {
            parent = root_;
            root_ = root_->leftChild;
            delete parent;
            parent = nullptr;
        }
        else if ((root_->rightChild != nullptr))
        {
            parent = root_;
            root_ = root_->rightChild;
            delete parent;
            parent = nullptr;
        }
        else
        {
            delete root_;
            root_ = nullptr;
        }
        return;
    }
    //处理正常情况
    if (parent->leftChild == cur)
    {
        parent->leftChild = (cur->leftChild == nullptr ? cur->rightChild : cur->leftChild);
    }
    else if (parent->rightChild == cur)
    {
        parent->rightChild = (cur->leftChild == nullptr ? cur->rightChild : cur->leftChild);
    }
    delete cur;
}

template <typename T, typename Comp>
bool BSTree<T, Comp>::n_query(T const& val)
{
    Node* cur = root_;
    while (cur != nullptr)
    {
        if (cur->data_ == val)
        {
            return true;
        }
        else if (comp_(cur->data_, val))
        {
            cur = cur->rightChild;
        }
        else
        {
            cur = cur->leftChild;
        }
    }
    return false;
}

template <typename T, typename Comp>
void BSTree<T, Comp>::preOrder(Node* node)
{
    if (node != nullptr)
    {
        cout << node->data_ << " ";
        preOrder(node->leftChild);
        preOrder(node->rightChild);
    }
    return;
}

template <typename T, typename Comp>
void BSTree<T, Comp>::inOrder(Node* node)
{
    if (node != nullptr)
    {
        inOrder(node->leftChild);
        cout << node->data_ << " ";
        inOrder(node->rightChild);
    }
    return;
}

template <typename T, typename Comp>
void BSTree<T, Comp>::postOrder(Node* node)
{
    if (node != nullptr)
    {
        postOrder(node->leftChild);
        postOrder(node->rightChild);
        cout << node->data_ << " ";
    }
    return;
}

//递归实现返回树的深度
template <typename T, typename Comp>
int BSTree<T, Comp>::high(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    int left = high(node->leftChild);
    int right = high(node->rightChild);
    return (left >= right) ? left + 1 : right + 1;
}

//递归返回节点个数
template <typename T, typename Comp>
int BSTree<T, Comp>::number(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    int left = number(node->leftChild);
    int right = number(node->rightChild);
    return left + right + 1;
}

//递归进行层级遍历
template <typename T, typename Comp>
void BSTree<T, Comp>::levelOrder(void)
{
    int depth = high();
    cout << "层级遍历:";
    for (int i = 0; i < depth; ++i)
    {
        levelOrder(root_, i);
    }
    cout << endl;
    return;
}

//递归进行层级遍历
template <typename T, typename Comp>
void BSTree<T, Comp>::levelOrder(Node* node, int level)
{
    if (node == nullptr)
        return;
    //当到达这一层时 才输出 这样保证了只在第n层输出第n层的节点内容
    if (level == 0)
    {
        cout << node->data_ << " ";
    }
    levelOrder(node->leftChild, level - 1);
    levelOrder(node->rightChild, level - 1);
    return;
}

//递归实现插入元素
template <typename T, typename Comp>
BSTree<T, Comp>::Node* BSTree<T, Comp>::insert(Node* node, const T& val)
{
    //当node为空时，说明找到了要插入的位置
    if (node == nullptr)
    {
        return new Node(val);
    }
    //当值重复时 不插入
    if (node->data_ == val)
    {
        return node;
    }
    if (comp_(node->data_, val))
    {
        //对子节点进行写入
        node->rightChild = insert(node->rightChild, val);
    }
    else
    {
        node->leftChild = insert(node->leftChild, val);
    }
    return node;
}

template <typename T, typename Comp>
BSTree<T, Comp>::Node* BSTree<T, Comp>::query(Node* node, const T& val)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->data_ == val)
    {
        return node;
    }
    if (comp_(node->data_, val))
    {
        return query(node->rightChild, val);
    }
    else
    {
        return query(node->leftChild, val);
    }
}

template <typename T, typename Comp>
BSTree<T, Comp>::Node* BSTree<T, Comp>::remove(Node* node, const T& val)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    //找到了
    if (node->data_ == val)
    {
        if (node->leftChild != nullptr && node->rightChild != nullptr)
        {
            //情况三：有两个孩子
            //解决方法：找前驱节点
            Node* pre = node->leftChild;
            while (pre->rightChild != nullptr)
            {
                pre = pre->rightChild;
            }
            node->data_ = pre->data_;
            //注意 此时原来的val值已经被覆盖 你需要删除的是前驱节点 所以要搜索前驱节点的值
            node->leftChild = remove(node->leftChild, pre->data_);
        }
        else if (node->leftChild != nullptr)
        {
            Node* temp = node->leftChild;
            delete node;
            return temp;
        }
        else if (node->rightChild != nullptr)
        {
            Node* temp = node->rightChild;
            delete node;
            return temp;
        }
        else
        {
            delete node;
            //无子节点
            return nullptr;
        }
    }
    else if (comp_(node->data_, val))
    {
        node->rightChild = remove(node->rightChild, val);
    }
    else
    {
        node->leftChild = remove(node->leftChild, val);
    }
    return node;
}

/*区间内查找元素
 *思路：使用的中序遍历的递归思路
 *当元素的值小于左边界时 不在遍历左子树 右边同理 可以增加效率
 */
template <typename T, typename Comp>
void BSTree<T, Comp>::findValues(Node* node, vector<T>& vec, int left, int right)
{
    if (node != nullptr)
    {
        if (node->data_ > left)
        {
            findValues(node->leftChild, vec, left, right);
        }
        if (node->data_ >= left && node->data_ <= right)
        {
            vec.push_back(node->data_);
        }
        if (node->data_ < right)
        {
            findValues(node->rightChild, vec, left, right);
        }
    }
}

/*通过中序遍历实现判断是否为BST树
 *首先 BST树有以下性质 整体：左子树的所有值都要小于根节点 右子树的所有值都要大于根节点
 *                  局部：左子节点<当前节点<右子节点
 *本函数通过BST中序遍历序列升序的特点 当发现如果不是升序的话 说明不是BST树 返回false
 *pre指向中序遍历中前一个节点的值 本函数将当前节点的值和前一个节点的值进行比较
 */
template <typename T, typename Comp>
bool BSTree<T, Comp>::isBSTree(Node* node, Node* pre)
{
    if (node == nullptr)
    {
        return true;
    }
    //L
    if (!isBSTree(node->leftChild, pre))
    {
        return false;
    }
    //V
    if (pre != nullptr)
    {
        if (comp_(node->data_, pre->data_))
        {
            return false;
        }
    }
    pre = node;
    //R
    if (!isBSTree(node->rightChild, pre))
    {
        return false;
    }
    return true;
}

void test01() // 测试是否是BST树
{
    using Node = BSTree<int>::Node;
    BSTree<int> bst;
    bst.root_ = new Node(40);
    Node* node1 = new Node(20);
    Node* node2 = new Node(60);
    Node* node3 = new Node(30);
    Node* node4 = new Node(80);

    bst.root_->leftChild = node1;
    bst.root_->rightChild = node2;
    node2->leftChild = node3;
    node2->rightChild = node4;

    cout << bst.isBSTree() << endl;
}

int main(void)
{
    BSTree<int> test1;
    int arr[] = {5, 4, 6, 2, 6, 7, 4, 99};
    for (auto i : arr)
    {
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
    for (auto i : arrr)
    {
        //test2.n_insert(i);
        test2.insert(i);
    }
    test2.remove(0);
    test2.preOrder();
    test2.n_preOrder();
    test2.inOrder();
    test2.n_inOrder();
    test2.postOrder();
    test2.n_postOrder();
    test2.levelOrder();
    test2.n_levelOrder();
    cout << test2.query(6);
    cout << test2.query(69);
    vector<int> vec1;
    test2.findValues(vec1, 20, 40);
    for (auto it : vec1)
    {
        cout << it << " ";
    }
    cout << endl;
    //是否为BST树测试
    cout << test1.isBSTree();
    test01();
    return 0;
}


