#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void split_string(char *str, char *string_1, char *string_2);

int main(void)
{
    char *str, *str_1, *str_2;

    str = (char *)malloc(51*sizeof(char));
    str_1 = (char *)malloc(51*sizeof(char));
    str_2 = (char *)malloc(26*sizeof(char));

    printf("input str : ");
    fgets(str, 50, stdin);

    split_string(str, str_1, str_2);

    printf("[%s] -> [%s] [%s]\n", str, str_1, str_2);

    return 0;
}

void split_string(char *str, char *string_1, char *string_2)
{
    int size;
    
    size = strlen(str)-1;
    *(str+size) = '\0';

    strcpy(string_1, str);
    if(size%2 != 0) {
        *(string_1 + (size-1)/2) = '\0';
        strcpy(string_2, str+(size-1)/2);
    }
    else {
        *(string_1 + size/2) = '\0';
        strcpy(string_2, str+size/2);
    }
}