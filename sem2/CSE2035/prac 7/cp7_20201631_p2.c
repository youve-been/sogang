#include <stdio.h>
#include <stdlib.h>

void double_double(int **a, int *size);
void sort(int *a, int size);
void swap(int *a, int *b);

int main(void)
{
    int *a;
    int size;

    scanf("%d", &size);

    a = (int *)calloc(size, sizeof(int));

    for(int i = 0; i < size; i++)
        scanf("%d", a+i);
    
    for(int i = 0; i < 3; i++) {
        double_double(&a, &size);
        size *= 2;
        for(int j = 0; j < size; j++)
            printf("%d ", *(a+j));
        printf("\n");
    }

    return 0;
}

void double_double(int **a, int *size)
{
    *a = (int *)realloc(*a, *size * 2 * sizeof(int));

    for(int i = 0; i < *size; i++)
        *(*a + *size+i) = *(*a+i) * 2;

    sort(*a, *size * 2);
}

void sort(int *a, int size)
{
    int min;

    for(int i = 0; i < size; i++) {
        min = i;

        for(int j = i+1; j < size; j++) {
            if(*(a+j) < *(a+min))
                min = j;
        }

        if(i != min)
            swap(a+i, a+min);
    }
}

void swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
