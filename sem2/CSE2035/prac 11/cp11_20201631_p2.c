#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_strncpy(char *a, char *b, int n);
void initialization(char *a, int n);

int main(void)
{
    int size;
    char *str, *str1;

    str = (char *)malloc(1001*sizeof(char));
    str1 = (char *)malloc(1001*sizeof(char));

    printf("input str : ");
    fgets(str1, 1000, stdin);

    size = strlen(str1)-1;
    *(str1-size) = '\0';

    for(int i = 0; i < size+1; i++) {
        initialization(str, size);
        my_strncpy(str, str1, i);
        printf("%s\n", str);
    }

    return 0;
}

char *my_strncpy(char *a, char *b, int n)
{
    char *tmp;

    for(int i = 0; i < n; i++)
        *(a+i) = *(b+i);
}

void initialization(char *a, int n)
{
    for(int i = 0; i < n; i++)
        *(a+i) = '*';
}