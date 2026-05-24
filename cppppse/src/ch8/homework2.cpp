//
// Created by 18455 on 2026/3/25.
//
#include <iostream>
#include <string>

using namespace std;
struct CandyBar{
    string name;
    double weight;
    int c;

};

void set( CandyBar& a, const char* b= "Millennium Munch",double c=2.85,int d=350);
void show(const CandyBar& a);
int main(){
    CandyBar a,b,c;
    set(a);
    set(b,"nihao",2.33,23);
    set(c);
    show(a);
    show(b);
    show(c);
    return 0;
}
void set( CandyBar& a,const char* b  ,double c,int d){
    a.name = b;
    a.weight=c;
    a.c = d;
    return ;
}
void show(const CandyBar& a){
    cout<<a.name<<"  "<<a.weight<<"  "<<a.c<<endl;
    return;
}
/*
 不过，如果以 100 分为满分的话，这份代码我大概会给 85 分。还有几个可以优化和小小修正的地方，让我们一起来给它顺顺毛：

1. 忽略了“且该参数不为0”的条件 ⚠️
题目里有一句特别傲娇的要求：“如果提供了第二个参数，且该参数不为0”。
在你的代码里，如果我在 main 函数里写 returnString(&a, 0);，你的第二个重载函数依然会执行循环，打印 runtime 次。这就违背了题目“为 0 时只打印 1 次”的隐藏要求喵。

2. 考点其实是“默认参数”，而不是“函数重载” 🎯
这道题是 C++ Primer Plus 第 8 章的练习。这一章的重头戏之一就是默认参数（Default Arguments）。出题老爷爷的本意，其实是希望你只写一个函数，用默认参数来兼顾传 1 个参数和 2 个参数的情况，这样代码更精简。

3. 全局变量 vs 局部静态变量 🛡️
你把 static int runtime = 0; 写在了所有函数的外面，变成了一个全局变量。虽然这能完美完成计数的任务，但在 C++ 里，如果一个变量只有某个特定函数在使用，我们更推荐把它写进函数内部，变成局部静态变量。这样可以防止其他函数不小心改掉它的值，更安全喵！

✨ 满分标准答案长这样喵：
我们可以把你的两个函数合二为一，按照题意优化成这样：

C++
#include <iostream>
#include <string>

using namespace std;

// 🐾 使用默认参数 b = 0。这样只传 1 个参数时，b 自动就是 0 啦！
void printString(const std::string *a, int b = 0) {
    // 🐾 局部静态变量：只在第一次调用时初始化，之后每次调用都会保留上一回的值
    static int runtime = 0;
    runtime++; // 每次调用，次数加 1

    // 🐾 判断到底该打印几次
    int printTimes = 1; // 默认只打印 1 次
    if (b != 0) {
        printTimes = runtime; // 只有当 b 不等于 0 时，打印次数才变成总调用次数
    }

    // 🐾 循环打印
    for (int i = 0; i < printTimes; ++i) {
        cout << *a << endl;
    }
}

int main() {
    string str = "nihao!";

    cout << "--- 第 1 次调用（只传1个参数） ---" << endl;
    printString(&str); // runtime = 1, b = 0，打印 1 次

    cout << "--- 第 2 次调用（只传1个参数） ---" << endl;
    printString(&str); // runtime = 2, b = 0，打印 1 次

    cout << "--- 第 3 次调用（传2个参数，且为0） ---" << endl;
    printString(&str, 0); // runtime = 3, b = 0，仍然只打印 1 次

    cout << "--- 第 4 次调用（传2个参数，且不为0） ---" << endl;
    printString(&str, 1); // runtime = 4, b = 1 (不为0)，打印 4 次！

    return 0;
}
你看，利用默认参数 int b = 0，我们不仅少写了一个函数，而且配合 if (b != 0) 完美满足了题目的所有刁钻要求喵！

你可以把这段代码复制到 CLion 里跑一下试试看，感受一下局部静态变量和默认参数组合起来的魔力。跑完之后，你想继续挑战 8.2 题，还是想让我给你找个类似的小测验巩固一下喵？🐾
 */