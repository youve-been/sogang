#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(char a, char b);

int main(void)
{
    char *str1, *str2;
    int size1, size2, i;

    str1 = (char *)malloc(1001*sizeof(char));
    str2 = (char *)malloc(1001*sizeof(char));

    fgets(str1, 1000, stdin);
    fgets(str2, 1000, stdin);
    size1 = strlen(str1) - 1;
    *(str1 + size1) = '\0';
    size2 = strlen(str2) - 1;
    *(str2 + size2) = '\0';

    if(size1 == size2) {
        for(i = 0; i <= size1; i++) {
            if(check(*(str1+i), *(str2+i)) == 0)
                break;
        }
        if(i > size1)
            printf("Equal\n");
        else
            printf("Not equal\n");
            
    }
    else
        printf("Not equal\n");
    
    return 0;
}

int check(char a, char b)
{
    int x1, x2;
    if(((a>=65)&&(a<=90))||((a>=97)&&(a<=122)))
        x1 = 1;
    else
        x1 = 0;
    
    if(((b>=65)&&(b<=90))||((b>=97)&&(b<=122)))
        x2 = 1;
    else
        x2 = 0;
    
    if(x1 == x2) {
        if(x1 == 1) {
            if((a==b)||(a == b + 32)||(a == b - 32))
                return 1;
            else
                return 0;
        }
        else {
            if(a == b)
                return 1;
            else
                return 0;
        }
        
    }
    else
        return 0;
}