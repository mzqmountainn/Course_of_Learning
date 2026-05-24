//strc_ref.cpp -- using structure references
#include <iostream>
#include <string>
//函数模板

struct data {
    std::string name;
    int value;
};

template <typename T>//函数模板
void swap(T &a,T &b){
    T temp;
    temp = a;
    a = b;
    b = temp;
}
template <> void swap<data>(data &a,data &b){ //显式具体化
    data temp;
    temp = a;
    a = b;
    b = temp;
}
template void swap<int>(int &a,int &b);//显式实例化

class test{
private:
    int a;
    char *b;
public:
    void show();
    test();
    ~test();
    test(int a_,char*b_);
};

test::test() {;}
test::test(int a_, char *b_) {
    a= a_;
    b = b_;
}

int main()
{
    int a = 10, b = 20;
    swap(a,b);
    std::cout << "a: " << a << ", b: " << b << std::endl;

    double x = 1.5, y = 2.5;
    swap(x,y);
    std::cout << "x: " << x << ", y: " << y << std::endl;

    data c = {"Alice", 30};
    data d = {"Bob", 25};
    swap(c,d);
    std::cout << "c: " << c.name << ", " << c.value << std::endl;
    return 0;
}

