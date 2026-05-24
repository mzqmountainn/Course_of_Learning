//
// Created by 18455 on 2026/5/17.
//
#include <iostream>

using namespace std;
enum State {
    STATE_UNUSE,
    STATE_USING,
    STATE_DEL
};

struct Bucket {
    int key_;
    State bucketState;
    Bucket(int key = 0, State state = STATE_UNUSE) : key_(key), bucketState(state) { ; }
};

class HashTable {
private:
    int tableNumber_;//长度
    double loadFactor_;//装载因子 useNumber/tableNumber
    Bucket *table_;
    int useNumber;//使用的数量
    static const int PRIME_SIZE = 10;//素数表大小
    static int primes_[PRIME_SIZE];//素数表
    int primeIndex_;//当前的素数下标
private:
    void expand(void) {
        int oldNumber = primes_[primeIndex_];
        primeIndex_++;
        if (primeIndex_ >= 10) {
            primeIndex_ = 9;
            throw "max";
        }
        Bucket *p = new Bucket[primes_[primeIndex_]];

        tableNumber_ = primes_[primeIndex_];
        for (int i = 0; i < oldNumber; ++i) {
            // 【关键修改：把状态判断提出来】
            // 如果是有效数据，才去算哈希并找新位置
            if (table_[i].bucketState == STATE_USING) {
                int numIdx = table_[i].key_ % tableNumber_;
                int numIdxoriginal = numIdx;

                do {
                    // 只要新表是空位，就放进去
                    if (p[numIdx].bucketState == STATE_UNUSE) {
                        p[numIdx].key_ = table_[i].key_;
                        p[numIdx].bucketState = STATE_USING;
                        break; // 放进去后跳出 do-while，处理旧表的下一个元素
                    }
                    // 否则继续往后探测找空位
                    numIdx = (numIdx + 1) % tableNumber_;
                } while (numIdx != numIdxoriginal);
            }
        }
        delete[]table_;
        table_ = p;
    }
public:
    HashTable(int size = 7, double loadFactor = 0.75) : useNumber(0), loadFactor_(loadFactor) {
        //确定大小
        for (primeIndex_ = 0; primeIndex_ < PRIME_SIZE; ++primeIndex_) {
            if (size <= primes_[primeIndex_]) {
                break;
            }
        }
        if (primeIndex_ == PRIME_SIZE)
            primeIndex_--;
        tableNumber_ = primes_[primeIndex_];
        table_ = new Bucket[tableNumber_];

    }
    ~HashTable() {
        delete[]table_;
        table_ = nullptr;
    }
    bool insert(int key) {
        //计算装载因子
        if (useNumber * 1.0 / tableNumber_ >= loadFactor_) {
            expand();
        }
        int keyIdx = key % tableNumber_;
        int keyIdxOriginal = keyIdx;
        do {
            if (table_[keyIdx].bucketState == STATE_UNUSE) {
                table_[keyIdx].key_ = key;
                table_[keyIdx].bucketState = STATE_USING;
                useNumber++;
                return true;
            }
            keyIdx = (keyIdx + 1) % tableNumber_;
        } while (keyIdx != keyIdxOriginal);
        return true;
    }
    bool find(int key) {
        int keyIdx = key % tableNumber_;
        int keyIdxOriginal = keyIdx;
        do {
            if (table_[keyIdx].bucketState == STATE_USING && table_[keyIdx].key_ == key) {

                return true;
            }
            keyIdx = (keyIdx + 1) % tableNumber_;
        } while (keyIdx != keyIdxOriginal && table_[keyIdx].bucketState != STATE_UNUSE);
        return false;
    }
    bool erase(int key) {
        int idx = key % tableNumber_;

        int i = idx;
        do {
            if (table_[i].bucketState == STATE_USING && table_[i].key_ == key) {
                table_[i].bucketState = STATE_DEL;
                useNumber--;
            }
            i = (i + 1) % tableNumber_;
        } while (table_[i].bucketState != STATE_UNUSE && i != idx);

        return true;
    }

};

int HashTable::primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

//int main() {
//    HashTable abc;
//    int i[] = {1, 2, 3, 4, 4, 5, 8};
//    for (int k: i) {
//        abc.Insert(k);
//    }
//}
int main() {
    HashTable htable;
    htable.insert(21);
    htable.insert(32);
    htable.insert(14);
    htable.insert(15);

    htable.insert(22);
    htable.insert(15);
    htable.insert(15);
    htable.insert(22);
    htable.insert(15);
    htable.insert(15);
    htable.insert(22);
    htable.insert(15);
    htable.insert(15);
    htable.insert(22);
    htable.insert(15);
    htable.insert(15);
    htable.insert(22);
    htable.insert(15);
    htable.insert(15);
    htable.insert(22);
    htable.insert(15);
    htable.insert(15);
    htable.insert(22);
    htable.insert(15);
    htable.insert(15);
    htable.insert(22);
    htable.insert(15);
    htable.insert(15);
    htable.insert(22);
    htable.insert(15);
    htable.insert(15);
    htable.insert(22);
    htable.insert(15);
    htable.insert(15);
    htable.insert(22);
    htable.insert(15);
    htable.insert(15);
    htable.insert(22);
    htable.insert(15);
    htable.insert(15);
    cout << htable.find(21) << endl;
    htable.erase(21);
    cout << htable.find(21) << endl;
}