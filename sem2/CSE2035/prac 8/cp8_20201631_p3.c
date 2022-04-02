#include <stdio.h>
#include <stdlib.h>

void square(int **a, int n);

int main(void)
{
    int **a;
    int n;

    scanf("%d", &n);

    a = (int **) malloc (sizeof(int *) * n);
    for(int i = 0; i < n; i++)
        a[i] = (int *) malloc (sizeof(int) * n);

    square(a,n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            printf("%2d ", a[i][j]);
        printf("\n");
    }

    return 0;
}

void square(int **a, int n)
{
    int count = 1;

    for(int i = 0, j = (n-1)/2; count <= n*n; i--, j++) {
        if(count%n == 1 && count != 1) {
            i += 2;
            j--;
        }

        if(i < 0)
            i = n-1;
        else if(i >= n)
            i = 0;

        if(j >= n)
            j = 0;

        a[i][j] = count;
        count++;
    }
}