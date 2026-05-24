// 20_大数据查重.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <unordered_set> 
#include <unordered_map>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

/*
查重的面试相关问题

有两个文件分别是a和b，里面放了很多ip地址(url地址、email地址)，让你找出来两个文件重复的ip，输出出来

==> 把a文件中所有的ip存放在一个哈希表中，然后依次遍历文件b里面的ip，每
遍历一个ip，在哈希表中搜索一下，搜到的，即是两个文件重复的ip并输出
    用到了哈希表的查询O(1)

有两个文件分别是a和b，各自存放在约1亿条ip地址，每个ip地址是4个字节限制内存使用100M，让找出来两个文件中重复的ip地址并输出

*/


#if 0
int main()
{
    string src = "jjhfgiyuhrtytrs";
    // 让你找出来第一个没有重复出现过的字符
    unordered_map<int, int> m;
    for (char ch : src)
    {
        m[ch]++;
    }

    for (char ch : src)
    {
        if (m[ch] == 1)
        {
            cout << "第一个没有重复出现过的字符是:" << ch << endl;
            return 0;
        }
    }

    cout << "所有字符都有重复出现过!" << endl;
    return 0;
}
#endif

#if 0
int main()
{
    // 模拟问题，vector中放原始的数据
    vector<int> vec;
    srand(time(NULL));
    for (int i = 0; i < 10000; i++)
    {
        vec.push_back(rand() % 10000);
    }

    // 找第一个出现重复的数字
    // 找所有重复出现的数字unordered_multiset
    //unordered_set<int> s1;
    //for (auto key : vec)
    //{
    //    auto it = s1.find(key); // O(1)
    //    if (it == s1.end())
    //    {
    //        s1.insert(key);
    //    }
    //    else
    //    {
    //        cout << "key:" << key << endl;
    //        break;
    //    }
    //}
    
    // 统计重复数字以及出现的次数
    unordered_map<int, int> m1;
    for (int key : vec)
    {
        // pair first second
        //auto it = m1.find(key); // O(1)
        //if (it == m1.end())
        //{
        //    m1.emplace(key, 1);  // O(1)
        //}
        //else
        //{
        //    it->second += 1;
        //}
        m1[key]++;
    }

    for (auto pair : m1)
    {
        if (pair.second > 1)
        {
            cout << "key:" << pair.first << " cnt:"
                << pair.second << endl;
        }
    }

    // 一组数据有些数字是重复的，把重复的数字过滤掉，每个数字只出现一次
    unordered_set<int> s1;
    for (auto key : vec)
    {
        s1.emplace(key);
    }
}
#endif
