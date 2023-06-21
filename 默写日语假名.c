#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int judge(int c,int v){
    int fin = 1;
    //去除假名中不存在的部分
    if(v==7){
        if( c== 1 | c==3 ){
            fin = 0;
        }
    }else if(v==9){
        if(c==1|c==2|c==3){fin = 0;}
    }
    return fin;
}
int main() {
    srand(time(NULL));
    int row=0;
    char *consonant[]={" ","k","s","t","n","h","m","y","r","w"};
    char *vowel[]={"a","i","u","e","o"};
    for (int q = 0; q < 10; ++q) {
        for (int i = 0; i < 10; i++) {
            int c =rand()%5;
            int r =rand()%10;
            if(judge(c,r))
              {
                  printf("%1s%1s  ",consonant[r],vowel[c]);
              } else
            {
                --i;
            }
            if (i==9){
                printf_s("\n\n\n");
            }
    }


    }

    getchar();
    return 0;


}

