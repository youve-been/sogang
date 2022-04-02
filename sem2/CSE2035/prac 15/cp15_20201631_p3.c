#include <stdio.h>

typedef struct {
    float real;
    float imag;
} complex;

complex *multiple(complex *a, complex *b);

int main(void)
{
    complex a, b, res;
    complex *pa = &a;
    complex *pb = &b;
    complex *pres = &res;

    scanf("%f %f", &pa->real, &pa->imag);
    scanf("%f %f", &pb->real, &pb->imag);

    pres = multiple(pa, pb);
    
    if(pres->imag > 0)
        printf("%.2f + (%.2f)i\n", pres->real, pres->imag);
    else
        printf("%.2f - (%.2f)i\n", pres->real, -(pres->imag));

    return 0;
}

complex *multiple(complex *a, complex *b)
{
    complex res;
    complex *pres = &res;

    pres->real = a->real*b->real - a->imag*b->imag;
    pres->imag = a->real*b->imag + a->imag*b->real;

    return pres;
}