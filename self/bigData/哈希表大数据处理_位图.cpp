//
// Created by mzq on 2026/5/27.
//
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

int main()
{
    vector<int> numbers{1,2,3,4,5,6,7,8,9,88,66,44,33,9};
    int max = numbers[0];
    for(int i=0;i<numbers.size();i++)
    {
        if (max<numbers[i])
            max = numbers[i];
    }
    int *bitmap = new int[max/32+1]();
    unique_ptr<int[]>ptr(bitmap);
    //cout<<"!";
    //q1:找到第一个重复的
    for (auto key:numbers)
    {
        int index = key/32;
        int offset = key%32;
        if ((bitmap[index]&(1<<offset)))
        {
            cout<<"第一个重复的数字是"<<key;
            return 0;
        }else
        {
            bitmap[index]|= (1<<offset);
        }
    }

}