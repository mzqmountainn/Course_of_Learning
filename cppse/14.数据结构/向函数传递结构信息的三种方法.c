/* funds1.c -- passing structure members as arguments */
#include <stdio.h>
#define FUNDLEN 50
struct funds {
    char   bank[FUNDLEN];
    double bankfund;
    char   save[FUNDLEN];
    double savefund;
};
double sum(double, double);
double sum1(const struct funds *);
double sum2(struct funds st);
int main(void)
{
    struct funds stan = {
        "Garlic-Melon Bank",
        4032.27,
        "Lucky's Savings and Loan",
        8543.94
    };
    
    printf("Stan has a total of $%.2f.\n",
           sum(stan.bankfund, stan.savefund) );//传递结构成员
    printf("Stan has a total of $%.2f.\n",
           sum1(&stan));//传递结构地址
    printf("Stan has a total of $%.2f.\n",
        sum2(stan));//传递结构
    return 0;
}
/* adds two double numbers */
double sum(double x, double y)
{
    return(x + y);
}
double sum1(const struct funds * money) {
    return(money->bankfund + money->savefund);
}
double sum2(struct funds st) {
    return(st.bankfund + st.savefund);
}
