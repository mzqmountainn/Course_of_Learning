//
// Created by 18455 on 2026/4/28.
//

//leetcode 20题
#include <string>
#include <stack>

using namespace std;
class Solution {
public:
    bool isValid(string s) {
        stack<char> cs;
        for (char n:s) {
            if(n=='('||n=='['||n=='{'){
                cs.push(n);
            } else{
                if(cs.empty())
                    return false;
                char val = cs.top();
                cs.pop();
                if(val=='('&&n!=')' || val=='['&&n!=']'||val=='{'&&n!='}' )
                    return false;
            }
        }
        return cs.empty();
    }
};