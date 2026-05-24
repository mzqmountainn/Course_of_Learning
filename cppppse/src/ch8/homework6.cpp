//
// Created by 18455 on 2026/3/26.
//

#include <iostream>
#include <span>
#include <cstring>

template<typename T>
T task( T *source,int num){
    T max = *source;
    for (int i = 0; i < num; ++i) {
        if(max<*(source+i)){
            max = *(source+i);
        }
    }
    std::cout<<max<<std::endl;
    return max;
}
template<> char* task<char*>(char** source,int num){
    char* max = *source;
    for (int i = 0; i < num; ++i) {
        //if(strcmp(max,*(source+i))<0){
        if(strlen(max) < strlen(*(source+i))){
            max = *(source+i);
        }
    }
    std::cout<<max<<std::endl;
    return max;
}


int main(){
    int a[6] = {1,4,8,2,878,5};
    double b[4] = {1.2,2.1,0.9,0.5};
    char *c[5]={(char *)"fdsf",
               (char *)   "fdsffsdf",
               (char *)  "a",
               (char *) "ff",
               (char *) "kkkkkkkkkkkk"

    };
    task(a,6);
    task(b,4);
    task(c,5);
    return 0;
}