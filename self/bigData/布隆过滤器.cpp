//
// Created by mzq on 2026/5/27.
//
//通过布隆过滤器实现网站黑名单
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include "stringHash.h"

using namespace std;

class BloomFilter
{
private:
    int bitSize_;
    std::vector<int> bitMap_;

public:
    BloomFilter(int size = 4099) : bitSize_(size)
    {
        bitMap_.resize(bitSize_ / 32 + 1);
    }

public:
    void setBit(const char* url)
    {
        int idx1 = BKDRHash(url) % bitSize_;
        int idx2 = SDBMHash(url) % bitSize_;
        int idx3 = RSHash(url) % bitSize_;
        bitMap_[idx1 / 32] |= (1 << (idx1 % 32));
        bitMap_[idx2 / 32] |= (1 << (idx2 % 32));
        bitMap_[idx3 / 32] |= (1 << (idx3 % 32));
    }

    bool getBit(const char* url)
    {
        int idx1 = BKDRHash(url) % bitSize_;
        int idx2 = SDBMHash(url) % bitSize_;
        int idx3 = RSHash(url) % bitSize_;
        if (0 == (bitMap_[idx1 / 32] & (1 << (idx1 % 32))))
            return false;
        if (0 == (bitMap_[idx2 / 32] & (1 << (idx2 % 32))))
            return false;
        if (0 == (bitMap_[idx3 / 32] & (1 << (idx3 % 32))))
            return false;
        return true;
    }
};

class BlockList
{
private:
    BloomFilter filter_;

public:
    void add(string url)
    {
        filter_.setBit(url.c_str());
    }

    bool query(string url)
    {
        return filter_.getBit(url.c_str());
    }
};

int main(void)
{
    BlockList test1;
    test1.add("http://4399.com");
    cout << test1.query("http://4399.com");
    cout << test1.query("http://43999.com");
}
