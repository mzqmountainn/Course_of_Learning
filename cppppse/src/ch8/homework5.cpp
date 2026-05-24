//
// Created by 18455 on 2026/3/26.
//
#include <iostream>

using namespace std;
template<typename T>
T max5(T *source){
    T max = *source;
    for (int i = 0; i < 5; ++i) {
        if(max< (*(source+i))){
            max = *(source+i);
        }
    }
    cout<<max<< endl;
    return max;
}


int main(){
    int a[5] = {1,2,3,4,6};
    double b[5]={4.4,5.5,6.6,7.7,8.8};
    max5(a);
    max5(b);
    return 0;
}