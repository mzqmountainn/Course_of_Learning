//
// Created by 18455 on 2026/3/25.
//
#include <iostream>
#include <string>
static int runtime =0;
using namespace std;
void returnString(const std::string *a){
    runtime++;
    cout<<*a<<endl;
}
void returnString(const std::string *a,int b){
    runtime++;
    for (int i = 0; i < runtime; ++i) {
        cout<<*a<<endl;
    }
}
int main(){
    string a = "nihao!";
    returnString(&a);
    returnString(&a);
    returnString(&a,1);
    return 0 ;
}


/*
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
 */