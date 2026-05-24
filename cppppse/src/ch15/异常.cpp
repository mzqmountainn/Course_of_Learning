//
// Created by 18455 on 2026/4/23.
//
#include <iostream>
#include <stdexcept> // 包含标准异常库

using namespace std;

// 1. 定义一个可能抛出异常的函数
double divide(double a, double b) {
    if (b == 0) {
        // 【抛出】遇到无法处理的错误，立刻扔出一个异常对象
        // std::invalid_argument 是 C++ 标准库提供的一种异常类型
        throw std::invalid_argument("除数不能为 0！");
    }
    // 如果 b 不为 0，程序才会走到这里
    return a / b;
}

int main() {
    cout << "程序开始运行..." << endl;

    // 2. 【尝试】把你觉得可能会出错的代码放进 try 块里
    try {
        cout << "尝试计算 10 / 2 = " << divide(10, 2) << endl; // 这句没问题

        cout << "尝试计算 10 / 0 = ";
        // 这一步会出错，divide 函数内部会 throw。
        // 一旦抛出异常，try 块内剩下的代码就不会再执行了！
        double result = divide(10, 0);

        cout << result << endl; // 这一行永远不会被打印出来
    }
        // 3. 【捕获】接住 throw 扔出来的错误
        // const exception& e 用于接收各种标准异常的引用
    catch (const std::exception& e) {
        // e.what() 可以提取我们在 throw 时写的那句错误提示
        cout << "\n[拦截到错误]: " << e.what() << endl;
        cout << "程序遇到错误，但没有崩溃，我们在这里进行了处理。" << endl;
    }

    cout << "程序安全结束。" << endl;
    return 0;
}