#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *str;
    int size;

    str = (char *)malloc(101*sizeof(char));
    scanf("%s", str);

    for(int i = 0 ; ; i++) {
        if(*(str+i) == '\0') {
            size = i;
            break;
        }
    }

    for(int i = 0; i < size; i++) {
        if(*(str+i) != *(str+size-i-1)) {
            printf("Not Palindrome.\n");
            break;
        }
        else if((i == (size-i-1))||(i == (size-i-2))){
            printf("Palindrome.\n");
            break;
        }
    }

    free(str);

    return 0;
}