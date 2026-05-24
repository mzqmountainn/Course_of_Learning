//
// Created by 18455 on 2026/4/13.
//
#include <iostream>
#include <string>

using namespace std;
class bank{
private:
    string name;
    string acc;
    int balance;
public:
    bank(string name_,string acc_,int balance_);
    void showInfo(void);
    void chargeIn(int number);
    void withdraw(int number);
};

bank::bank(std::string name_, std::string acc_, int balance_) {
    name = name_;
    acc = acc_;
    balance = balance_;
}
void bank::showInfo(void) {
    cout<<name<<acc<<balance<<endl;

}
void bank::chargeIn(int number) {
    balance+=number;
}
void bank::withdraw(int number) {
    if(balance>=number){
        balance-=number;
    } else{
        cout<<"fail!"<<endl;
    }
}


int main(){
    bank myacc {"mzq","114514",5000};
    myacc.showInfo();
    myacc.chargeIn(1000);
    myacc.showInfo();
    myacc.withdraw(4000);
    myacc.showInfo();
    return 0;
}