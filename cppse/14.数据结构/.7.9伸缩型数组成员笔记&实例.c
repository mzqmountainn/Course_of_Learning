// flexmemb.c -- flexible array member (C99 feature)
//伸缩性数组成员



/*2个特性：该数组不会立刻存在，并且可以编写合适的代码
  须遵守如下规则
     1.伸缩型数组成员必须是结构的最后一个成员
     2.结构中必须至少有一个成员
     3.伸缩数组的生命类似于普通数组，只是他的方括号中是空的
     详细见实例*/
#include <stdio.h>
#include <stdlib.h>

struct flex
{
    size_t count;
    double average;
    double scores[];   // flexible array member
};

void showFlex(const struct flex * p);

int main(void)
{
    struct flex * pf1, *pf2;
    int n = 5;
    int i;
    int tot = 0;
    
    // allocate space for structure plus array
    pf1 = malloc(sizeof(struct flex) + n * sizeof(double));//分配内存
    pf1->count = n;
    for (i = 0; i < n; i++)
    {
        pf1->scores[i] = 20.0 - i;
        tot += pf1->scores[i];
    }
    pf1->average = tot / n;
    showFlex(pf1);
    
    n = 9;
    tot = 0;
    pf2 = malloc(sizeof(struct flex) + n * sizeof(double));
    pf2->count = n;
    for (i = 0; i < n; i++)
    {
        pf2->scores[i] = 20.0 - i/2.0;
        tot += pf2->scores[i];
    }
    pf2->average = tot / n;
    showFlex(pf2);
    free(pf1);
    free(pf2);
    
    return 0;
}

void showFlex(const struct flex * p)
{
    int i;
    printf("Scores : ");
    for (i = 0; i < p->count; i++)
        printf("%g ", p->scores[i]);
    printf("\nAverage: %g\n", p->average);
}
