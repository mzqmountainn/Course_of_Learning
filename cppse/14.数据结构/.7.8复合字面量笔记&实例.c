/* complit.c -- compound literals */
//复合字面量和结构（c99）

/*如果需要一个临时结构值，复合字面量很好用
语法： (struct book) {"dwed","fewf",9.99}
*/

//把复合字面量作为函数的参数。如果函数接受一个结构，可以把复合字面量作为实参传递
struct rect { double x; double y };
double rect_area(struct rect r) { return r.x * r.y; }
//.....
double area;
area = rect_area((struct rect) { 10.5, 20.0 });

//传递复合字面量的地址
struct rect { double x; double y };
double rect_areap(struct rect * rp) { return rp->x * rp->y; }
//...
double area;
area = rect_areap(&(struct rect) { 10.5, 20.0 });



//实例
#include <stdio.h>
#define MAXTITL  41
#define MAXAUTL  31

struct book {          // structure template: tag is book
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
};

int main(void)
{
    struct book readfirst;
    int score;
    
    printf("Enter test score: ");
    scanf("%d",&score);
    
    if(score >= 84)
        readfirst = (struct book) {"Crime and Punishment",
            "Fyodor Dostoyevsky",
            11.25};
    else
        readfirst = (struct book) {"Mr. Bouncy's Nice Hat",
            "Fred Winsome",
            5.99};
    printf("Your assigned reading:\n");
    printf("%s by %s: $%.2f\n",readfirst.title,
           readfirst.author, readfirst.value);
    
    return 0;
}
