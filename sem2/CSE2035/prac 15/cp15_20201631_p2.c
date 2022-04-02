#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float price;
    float number;
} Buying;

Buying getAverage(Buying *pBuying, int n);

int main(void)
{
    int n;
    Buying *pBuying, avg;

    scanf("%d", &n);

    pBuying = (Buying *)malloc(sizeof(Buying)*n);

    for(int i = 0; i < n; i++) {
        scanf("%f %f", &pBuying[i].price, &pBuying[i].number);
    }

    avg = getAverage(pBuying, n);

    printf("%.2f %.2f\n", avg.price, avg.number);

    return 0;
}

Buying getAverage(Buying *pBuying, int n)
{
    float avg_p = 0;
    float avg_n = 0;
    Buying avg;

    for(int i = 0; i < n; i++) {
        avg_p += pBuying[i].price;
        avg_n += pBuying[i].number;
    }

    avg.price = avg_p/n;
    avg.number = avg_n/n;

    return avg;
}