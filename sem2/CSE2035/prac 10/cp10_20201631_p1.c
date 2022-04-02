#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *str;
    int i;
    int count = 0;

    str = (char *)malloc(501*sizeof(char));

    fgets(str, 500, stdin);

    for(i = 0; ; i++) {
        if(*(str+i) == '\0') {
            printf("0\n");
            return 0;
        }
        else if(*(str+i) != 32) {
            i++;
            count++;
            break;
        }
    }

    for(; *(str+i) != '\0'; i++) {
        if((*(str+i-1) == 32)&&(((*(str+i)>=65)&&(*(str+i)<=90))||((*(str+i)>=97)&&(*(str+i)<=122))))
            count++;
    }

    printf("%d\n", count);

    return 0;
}