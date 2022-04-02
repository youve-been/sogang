#include <stdio.h>
#include <stdlib.h>

int determinant(int **a);

int main(void) {
    int **a;
    double det;

    a = (int **) malloc (sizeof(int *) * 2);
    a[0] = (int *) malloc (sizeof(int) * 2);
    a[1] = (int *) malloc (sizeof(int) * 2);

    scanf("%d %d", &a[0][0], &a[0][1]);
    scanf("%d %d", &a[1][0], &a[1][1]);

    det = (double)determinant(a);

    if(det == 0)
        printf("Singular Matrix\n");
    else {
        printf("Invertible Matrix\n");
        printf("%.2lf %.2lf\n", a[1][1]/det, -a[0][1]/det);
        printf("%.2lf %.2lf\n", -a[1][0]/det, a[0][0]/det);
    }

    return 0;
}

int determinant(int **a)
{
    int det;

    det = a[0][0]*a[1][1] - a[0][1]*a[1][0];

    return det;
}