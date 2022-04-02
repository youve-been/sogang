#include <stdio.h>
#include <stdlib.h>

void push_back(int **a, int *size, int value);
void pop_back(int **a, int *size);
double average(int *a, int size);
double variance(int *a, int size);

int main(void)
{
    int n, choice;
    int size = 0;
    int *a;
    int value;
    double avg;
    double var;

    scanf("%d", &n);

    a = (int *)calloc(1, sizeof(int));

    while(n>0) {
        scanf("%d", &choice);

        if(choice == 1) {
            scanf("%d", &value);

            size++;            
            push_back(&a, &size, value);

            avg = average(a, size);
            var = variance(a, size);
        }
        else {
            size--;

            pop_back(&a, &size);

            avg = average(a, size);
            var = variance(a, size);
        }

        for(int i = 0; i < size; i++)
            printf("%d ", *(a+i));
        printf("\n");

        printf("%lf %lf\n", avg, var);

        n--;
    }

    return 0;
}

void push_back(int **a, int *size, int value)
{
    *a = (int *)realloc(*a, *size * sizeof(int));
    *(*a + (*size-1)) = value;
}

void pop_back(int **a, int *size)
{
    *a = (int *)realloc(*a, *size * sizeof(int));
}

double average(int *a, int size)
{
    double avg;
    int sum = 0;

    for(int i = 0;i < size; i++)
        sum += *(a+i);
    
    avg = (double)sum / size;

    return avg;
}

double variance(int *a, int size)
{
    double avg, var;
    double sum = 0;

    for(int i = 0;i < size; i++)
        sum += *(a+i);
    
    avg = sum / size;

    sum = 0;

    for(int i = 0; i < size; i++)
        sum += (*(a+i) - avg) * (*(a+i) - avg);
    
    var = sum / size;

    return var;
}