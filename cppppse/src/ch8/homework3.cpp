//
// Created by 18455 on 2026/3/25.
//
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
void task(string &str){
    for (int i = 0; i < str.length(); ++i) {
        str[i] = toupper(str[i]);
    }
}

int main(){
    string input;
    while(1){
        cout<<"Enter a string (q to quit):";
        getline(cin,input);
        if (input == "q"){
            cout<<"Bye.";
            break;
        }
        task(input);
        cout<<input<<endl;
    }
    return 0;
}