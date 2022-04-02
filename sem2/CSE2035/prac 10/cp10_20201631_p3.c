#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *str;
    char *tmp;
    int index = 0;

    str = (char *)malloc(201*sizeof(char));
    tmp = (char *)malloc(201*sizeof(char));

    printf("Input string : ");
    fgets(str, 200, stdin);
    
    for(int i = 0; ; i++) {
        if(*(str+i) == '\0') {
            *(str+i-1) = '\0';
            break;
        }
    }

    printf("- Result -\n");

    for(int i = 0; ; i++) {
        if(*(str+i) == 32) {
            printf("\t%s\n", tmp);
            for(int j = 0; j < index; j++)
                *(tmp + j) = '\0';
            index = 0;
        }
        else if (*(str+i) == '\0') {
            printf("\t%s\n", tmp);
            break;
        }
        else {
            *(tmp+index) = *(str+i);
            index++;
        }
    }

    return 0;
}