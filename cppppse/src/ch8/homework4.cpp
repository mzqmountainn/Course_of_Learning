//
// Created by 18455 on 2026/3/26.
//
#include <iostream>
#include <cstring>

using namespace std;

struct stringy {
    char *str;
    int ct;
};
void set(stringy& target,const char* source){
    //target.str = new char[strlen(source)];
    target.str = new char[strlen(source)+1];//此处注意+1！！
    strcpy(target.str,source);
}
void show(const stringy& source,int time =1){
    for (int i = 0; i < time; ++i) {
        cout<<source.str<<endl;
    }
}
void show(const char* source="nothing",int time=1){
    for (int i = 0; i < time; ++i) {
        cout<<source<<endl;
    }

}

int main() {
    stringy beany;
    char testing[] = "Reality isn't what it used to be.";

    set(beany, testing);
    show(beany);
    show(beany, 2);
    testing[0] = 'D';
    testing[1] = 'u';
    show(testing);
    show(testing, 3);
    show("Done!");
    delete[] beany.str; // 喵~ 打扫干净房间再离开
    return 0;
}