// 19_链式哈希表.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

// 链式哈希表
class HashTable
{
public:
	HashTable(int size = primes_[0], double loadFactor = 0.75)
		: useBucketNum_(0)
		, loadFactor_(loadFactor)
		, primeIdx_(0)
	{
		if (size != primes_[0])
		{
			for (; primeIdx_ < PRIME_SIZE; primeIdx_++)
			{
				if (primes_[primeIdx_] >= size)
					break;
			}

			if (primeIdx_ == PRIME_SIZE)
			{
				primeIdx_--;
			}
		}

		table_.resize(primes_[primeIdx_]);
	}

public:
	// 增加元素 不能重复插入key
	void insert(int key)
	{
		// 判断扩容
		double factor = useBucketNum_ * 1.0 / table_.size();
		cout << "factor:" << factor << endl;
		if (factor > loadFactor_)
		{
			expand();
		}

		int idx = key % table_.size();  // O(1)
		if (table_[idx].empty())
		{
			useBucketNum_++;
			table_[idx].emplace_front(key);
		}
		else
		{
			// 使用全局的::find泛型算法，而不是调用自己的成员方法find
			auto it = ::find(table_[idx].begin(), table_[idx].end(), key);  // O(n)
			if (it == table_[idx].end())
			{
				// key不存在
				table_[idx].emplace_front(key);
			}
		}
	}

	// 删除元素
	void erase(int key)
	{
		int idx = key % table_.size();  // O(1)
		// 如果链表节点过长：如果散列结果比较集中（散列函数有问题！！！）
		//                 如果散列结果比较离散，链表长度一般不会过程，因为有装载因子
		auto it = ::find(table_[idx].begin(), table_[idx].end(), key); // O(n)
		if (it != table_[idx].end())
		{
			table_[idx].erase(it);
			if (table_[idx].empty())
			{
				useBucketNum_--;
			}
		}
	}

	// 搜索元素
	bool find(int key)
	{
		int idx = key % table_.size();  // O(1)
		auto it = ::find(table_[idx].begin(), table_[idx].end(), key); // 
		return it != table_[idx].end();
	}

private:
	// 扩容函数
	void expand()
	{
		if (primeIdx_ + 1 == PRIME_SIZE)
		{
			throw "hashtable can not expand anymore!";
		}

		primeIdx_++;
		useBucketNum_ = 0;

		vector<list<int>> oldTable;
		// swap会不会效率很低？？？ 交换了两个容器的成员变量
		table_.swap(oldTable);
		table_.resize(primes_[primeIdx_]);

		for (auto list : oldTable)
		{
			for (auto key : list)
			{
				int idx = key % table_.size();
				if (table_[idx].empty())
				{
					useBucketNum_++;
				}
				table_[idx].emplace_front(key);
			}
		}
	}

private:
	vector<list<int>> table_; // 哈希表的数据结构
	int useBucketNum_;        // 记录桶的个数
	double loadFactor_;       // 记录哈希表装载因子

	static const int PRIME_SIZE = 10; // 素数表的大小
	static int primes_[PRIME_SIZE];   // 素数表
	int primeIdx_; // 当前使用的素数下标
};

int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };


int main()
{
	HashTable htable;
	htable.insert(21);
	htable.insert(32);
	htable.insert(14);
	htable.insert(15);

	htable.insert(22);

	htable.insert(67);

	cout << htable.find(67) << endl;
	htable.erase(67);
	cout << htable.find(67) << endl;

	return 0;
}