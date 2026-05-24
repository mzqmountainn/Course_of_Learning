//
// Created by 18455 on 2026/5/19.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

class HashTable {
private:
    static const int PRIME_SIZE = 10; // 素数表的大小
    static int primes_[PRIME_SIZE];   // 素数表
    int primeIdx_; // 当前使用的素数下标

    vector<list<int>> table_;
    int useBucket_;
    double loadFactor_;
private:
    void expand(void) {
        if (primeIdx_ + 1 == 10)
            throw "fail to expand";
        primeIdx_++;
        vector<list<int>> oldTable;
        table_.swap(oldTable);
        table_.resize(primes_[primeIdx_]);

    }
public:
    HashTable(int size = 7, double loadFactor = 0.75) : loadFactor_(loadFactor), useBucket_(0) {
        for (int i = 0; i < PRIME_SIZE; ++i) {
            if (primes_[i] >= size) {
                primeIdx_ = i;
                break;
            }
        }
        if (primeIdx_ == PRIME_SIZE)
            primeIdx_--;
        table_.resize(primes_[primeIdx_]);
    }
    void insert(int key) {
        if (useBucket_ * 1.0 / primes_[primeIdx_] >= loadFactor_)
            expand();
        int keyIndex = key % primes_[primeIdx_];
        if (table_[keyIndex].empty()) {
            table_[keyIndex].emplace_front(key);
            useBucket_++;
        } else {
            //先查重
            auto it = ::find(table_[keyIndex].begin(), table_[keyIndex].end(), key);
            if (it == table_[keyIndex].end())
                table_[keyIndex].emplace_front(key);
        }
    }
    bool erase(int key) {
        int keyIndex = key % primes_[primeIdx_];
        if (table_[keyIndex].empty()) {
            return false;
        }
        auto it = ::find(table_[keyIndex].begin(), table_[keyIndex].end(), key);
        if (it != table_[keyIndex].end()) {
            table_[keyIndex].erase(it);
            if (table_[keyIndex].empty())
                useBucket_--;
        }
        return true;
    }
    bool find(int key) {
        int keyIndex = key % primes_[primeIdx_];
        auto it = ::find(table_[keyIndex].begin(), table_[keyIndex].end(), key);
        return (it != table_[keyIndex].end());
    }
};

int HashTable::primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

//int main() {
//    HashTable abc;
//    int i[] = {1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8};
//    for (int k: i) {
//        abc.insert(k);
//    }
//}
int main() {
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
