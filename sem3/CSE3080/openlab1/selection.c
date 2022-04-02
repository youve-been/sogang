#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x, y, t)  ((t)=(x), (x)=(y), (y)=(t))

void sort(int list[], int n)
{
    int i, j, min, temp;
    for(i = 0; i < n-1; i++) {
        min = i;
        for(j = i+1; j < n; j++) {
            if(list[j] < list[min])
                min = j;
        }
        SWAP(list[i], list[min], temp);
    }
}

int main(void)
{
    int i, step = 10;
    int *a, *tmp, size;
    clock_t start;
    double duration, dur_useless;
    FILE *fp;

    fp = fopen("lab1.data", "rt");

    fscanf(fp, "%d", &size);
    tmp = (int *)malloc(sizeof(int)*size);
    a = (int *)malloc(sizeof(int)*size);
    for(i = 0; i < size; i++)
        fscanf(fp, "%d", &tmp[i]);

    printf("Input : ");
    for(i = 0; i < size; i++)
        printf("%d ", tmp[i]);
    printf("\n");

    long repetitions = 0;

    start=clock();
    do {
        for(i = 0; i < size; i++)
            a[i] = tmp[i];
        repetitions++;
        sort(a, size);
    } while(clock() - start < 10000);
    

    duration = ((double) (clock() - start)) / CLOCKS_PER_SEC;
    duration /= repetitions;

    printf("Sorted : ");
    for(i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");

    printf("Repetitions : %ld\n", repetitions);
    printf("Duration : %lf\n", duration);

    fclose(fp);
    free(a);

    return 0;
}