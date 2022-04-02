#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int **table;
    int n, m;

    scanf("%d %d", &n, &m);

    table = (int **) malloc (sizeof(int *) * n);
    for(int i = 0; i < n; i++) {
        table[i] = (int *) malloc (sizeof(int) * m);
        table[i][0] = 1;
    }
    
    for(int i = 0; i < m; i++) {
        table[0][i] = 1;
    }

    for(int i = 1; i < n; i++) {
        for(int j = 1; j < m; j++)
            table[i][j] = table[i-1][j] + table[i][j-1];
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            printf("%d ", table[i][j]);
        printf("\n");
    }

    return 0;
}