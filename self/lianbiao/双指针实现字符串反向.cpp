#include <iostream>
#include <string.h>

using namespace std;
void reserves(char array[], int size) {
    char *p, *q;
    char ch;
    p = array;
    q = array + size - 1;
    while (p < q) {
        ch = *p;
        *p = *q;
        *q = ch;
        p++;
        q--;
    }
}
int removeElement(int *nums, int numsSize, int val) {
    int *p, *q;
    p = nums;
    q = nums + numsSize - 1;
    while (p <= q) {
        if (*q == val) {
            q--;
            continue;
        }

        if (*p == val) {
            *p = *q;
            q--;
        }
        p++;

    }
    return p - nums;
}

int main() {
    char a[] = "hello world";
    char b[] = "nihao!!!";
    reserves(a, strlen(a));
    cout << a << endl;
    reserves(b, strlen(b));
    cout << b;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
