#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char **str, int a);

int main(void) {
    int n, k;
    char **str;

    scanf("%d", &n);

    str = (char **)malloc(n*sizeof(char *));
    for(int i = 0; i < n; i++) {
        *(str+i) = (char *)malloc(1001*sizeof(char));
        scanf("%s", *(str+i));
    }

    for(int j = 0; j < n-1; j++) {
        for(int i = 0; i < n-1; i++) {
            k = strcmp(*(str+i), *(str+i+1));
            if(k > 0)
                swap(str, i);
        }
    }

    printf("-Lexicographic Order-\n");
    for(int i = 0; i < n; i++) {
        printf("%s\n", *(str+i));
    }

    return 0;
}

void swap(char **str, int a)
{
    int size_a, size_b;
    char *tmp;

    tmp = (char *)malloc(1001*sizeof(char));

    size_a = strlen(*(str+a));
    size_b = strlen(*(str+a+1));

    strcpy(tmp, *(str+a));
    strcpy(*(str+a), *(str+a+1));
    *(*(str+a)+size_b) = '\0';
    strcpy(*(str+a+1), tmp);
    *(*(str+a+1)+size_a) = '\0';
}