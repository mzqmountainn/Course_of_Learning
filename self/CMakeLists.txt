cmake_minimum_required(VERSION 3.27)
project(self)

set(CMAKE_CXX_STANDARD 23)

add_executable(self #双指针实现字符串反向.cpp
        #lianbiao/单链表.cpp
        #"lianbiao/leetcode_删除链表的倒数第 N 个结点.cpp"
        #lianbiao/单向循环链表.cpp
        #lianbiao/约瑟夫环.cpp
        #lianbiao/双向链表.cpp
        #stack/顺序栈.cpp
        #stack/链式栈.cpp
        #stack/leetcode_有效的括号.cpp
        #stack/lletcode_逆波兰表达式求值.cpp
        #stack/中辍表达式转后辍表达式.cpp
        #cmake-build-debug/queue/环形队列.cpp
        #cmake-build-debug/queue/leetcode_用栈实现队列.cpp
        #cmake-build-debug/queue/leetcode_用队列实现栈.cpp
        #search/二分搜索.cpp
        #sort/基础排序.cpp
        #sort/快速排序.cpp
        #sort/归并排序.cpp
        #sort/二叉堆.cpp
        #sort/堆排序.cpp
        #hash/线性探测哈希表.cpp
        #hash/链式哈希表.cpp
        bigData/哈希表大数据处理.cpp
)
