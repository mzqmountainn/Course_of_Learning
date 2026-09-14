//
// Created by mzq on 2026/9/14.
//
#include <iostream>
#include <algorithm>
using namespace std;

/*
m个柜台提供服务，每个柜台给一个用户提供服务的时间是t(用数组表示每一个柜台提供服务的时间)，
问怎么排列，使得柜台给所有用户提供服务的时间最少？
*/

struct Counter
{
    int id;
    int time;
    int number;

    bool operator<(const Counter& counter2) const
    {
        return time < counter2.time;
    }
};

int main(void)
{
    int timeCost[] = {2, 3, 4};
    int minTime = 0;
    const int n = sizeof(timeCost) / sizeof(timeCost[0]);
    const int custonmerNumber = 15;
    Counter counter[n];
    for (int i = 0; i < n; ++i)
    {
        counter[i].id = i;
        counter[i].time = timeCost[i];
        counter[i].number = 0;
    }
    sort(counter, counter + n);
    for (int i = 0; i < custonmerNumber; ++i)
    {
        int timeConsume = (counter[0].number + 1) * counter[0].time;
        int j = 1;
        for (; j < n; j++)
        {
            int t = (counter[j].number + 1) * counter[j].time;
            if (t < timeConsume)
            {
                counter[j].number++;
                if (t > minTime)
                {
                    minTime = t;
                }
                break;
            }
        }
        //进入条件：放在第一个柜台时间最短
        if (j == n)
        {
            counter[0].number++;
            if (timeConsume > minTime)
            {
                minTime = timeConsume;
            }
        }
    }
    for (auto it : counter)
    {
        cout << it.number << " ";
    }
    cout << endl;
    cout << minTime;
    return 0;
}
