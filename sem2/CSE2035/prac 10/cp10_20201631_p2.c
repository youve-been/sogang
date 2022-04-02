#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *str;
    char *target;
    int size, count = 0;

    str = (char *)malloc(501*sizeof(char));
    target = (char *)malloc(101*sizeof(char));

    printf("Text : ");
    fgets(str, 500, stdin);
    printf("Word : ");
    fgets(target, 100, stdin);

    for(int i = 0 ; ; i++) {
        if(*(target+i) == '\0') {
            size = i-1;
            *(target+i-1) = '\0';
            break;
        }
    }

    for(int i = 0; *(str+i) != '\0'; i++) {
        if(*(str+i) == *target) {
            for(int j = 0; j <= size; j++, i++) {
                if((*(str+i) == 32)&&(*(target+j) == '\0')) {
                    count++;
                }
                if(*(str+i) != *(target+j))
                    break;
            }
        }
    }

    printf("Number of '%s' : %d\n", target, count);
    
    return 0;
}
