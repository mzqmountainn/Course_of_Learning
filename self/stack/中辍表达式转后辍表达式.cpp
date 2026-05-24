//
// Created by 18455 on 2026/5/5.
//
/*
 中缀=>后缀
遇到数字，直接输出
遇到符号：
1、栈为空，符号直接入栈
2、如果是（，直接入栈
3、用当前符号和栈顶符号比较其优先级
当前符号>栈顶符号当前符号直接入栈，结束
当前符号<=栈顶符号
栈顶符号出栈并输出，继续比
较
把栈里面的符号都出完了
2、遇到，要一直出栈，直到遇见
（为止
 */
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// 比较优先级：返回 true 表示 ch 的优先级高于 topch，需要入栈
bool compare(char ch, char topch) {
    // 修复3：只要当前字符是左括号，无条件入栈
    if (ch == '(')
        return true;
    if ((ch == '*' || ch == '/') && (topch == '+' || topch == '-'))
        return true;
    if (topch == '(' && ch != ')')
        return true;
    return false;
}

string prefixToSuffix(string source) {
    string result;
    stack<char> cStack;
    for (char ch: source) {
        if (ch >= '0' && ch <= '9') {
            result.push_back(ch); // 数字直接输出
        } else {
            while (1) {
                // 修复1：栈为空时，不仅是 '('，其他运算符也要入栈
                if (cStack.empty()) {
                    if (ch != ')') {
                        cStack.push(ch);
                    }
                    break;
                }

                // 修复2：专门处理右括号的退栈逻辑
                if (ch == ')') {
                    if (cStack.top() == '(') {
                        cStack.pop(); // 遇到左括号，弹出并结束
                        break;
                    } else {
                        result.push_back(cStack.top());
                        cStack.pop();
                    }
                }
                    // 常规运算符比较优先级
                else if (compare(ch, cStack.top())) {
                    cStack.push(ch);
                    break;
                } else {
                    // 优先级不高于栈顶，持续弹出栈顶元素
                    result.push_back(cStack.top());
                    cStack.pop();
                }
            }
        }
    }

    // 表达式遍历完后，将栈内剩余的运算符全部输出
    while (!cStack.empty()) {
        if (cStack.top() != '(' && cStack.top() != ')')
            result.push_back(cStack.top());
        cStack.pop();
    }
    return result;
}

int main(void) {
    cout << prefixToSuffix("(1+2)*(3+4)") << endl;       // 预期输出: 12+34+*
    cout << prefixToSuffix("2+(4+6)/2+6/3") << endl;     // 预期输出: 246+2/+63/+
    cout << prefixToSuffix("2+6/(4-2)+(4+6)/2") << endl; // 预期输出: 2642-/+46+2/+
    return 0;
}



//#include <iostream>
//#include <stack>
//#include <string>
//
//using namespace std;
//
//bool t = true;
//bool meetLeft = false;
//// ture ch > topch (优先级)
//bool compare(char ch, char topch) {
////    if (topch == '(' && t == false)
////        t = true;
////    if (t == false)
////        return false;
////    if ((ch == '/' || ch == '*') && (topch == '-' || topch == '+'))
////        return true;
////    if ((ch == '/' || ch == '*'||ch == '-' || ch == '+')&&topch=='(')
////        return true;
////    if (ch == '(') {
////        meetLeft= true;
////        return true;
////    }
////    if (ch == ')') {
////        t = false;
////        meetLeft = false;
////        return false;
////    }
////
////
////    return false;
//    if ((ch == '*' || ch == '/') && (topch == '+' || topch == '-'))
//        return true;
//    if (topch == '(' && ch != ')')
//        return true;
//    return false;
//}
//string prefixToSuffix(string source) {
//    string result;
//    stack<char> cStack;
//    for (char ch: source) {
//        if (ch >= '0' && ch <= '9') {
//            result.push_back(ch);
//        } else {
//            while (1) {
//                if (cStack.empty()) {
//                    if(ch == '(')
//                        cStack.push(ch);
//                    break;
//                }
//                if (compare(ch, cStack.top())) {
//                    cStack.push(ch);
//                    break;
//                } else {
//                    if (cStack.top() != '(' && cStack.top() != ')') {
//                        result.push_back(cStack.top());
//                    }
//                    cStack.pop();
//                }
//            }
//        }
//    }
//    while (!cStack.empty()) {
//        if (cStack.top() != '(' && cStack.top() != ')')
//            result.push_back(cStack.top());
//        cStack.pop();
//    }
//    return result;
//}
//int main(void) {
//    cout << prefixToSuffix("(1+2)*(3+4)") << endl;
//    cout << prefixToSuffix("2+(4+6)/2+6/3") << endl;
//    cout << prefixToSuffix("2+6/(4-2)+(4+6)/2") << endl;
//}