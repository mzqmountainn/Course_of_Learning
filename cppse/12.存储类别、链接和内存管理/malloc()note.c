/*动态分配内存
函数：malloc()*/
//用法举例：
#include<stdlib.h>
double* ptd;
ptd = (double*) malloc(30 * sizeof(double));
double item[n];//c99前不可
ptd = (double*)malloc(n * sizeof(double));

double * ptd = (double*)malloc(n * sizeof(double));//简化版