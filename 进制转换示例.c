#include <stdio.h>
void to_base_n(int x, int base);
int main(void)
{
    int number;
    int b;
    int count;

    printf("Enter an integer (q to quit):\n");
    while (scanf("%d", &number) == 1)
    {
        printf("Enter number base (2-10): ");
        while ((count = scanf("%d", &b))== 1
               && (b < 2 || b > 10))
        {
            printf("base should be in the range 2-10: ");
        }
        if (count != 1)
            break;
        printf("Base %d equivalent: ", b);
        to_base_n(number, b);
        putchar('\n');
        printf("Enter an integer (q to quit):\n");
    }
    printf("Done.\n");
    return 0;
}
void to_base_n(int x, int base) /* recursive function */
{
    int r;
    r = x % base;
    if (x >= base)
        to_base_n(x / base, base);
    putchar('0' + r);
    return;
}