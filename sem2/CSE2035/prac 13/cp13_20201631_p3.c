#include <stdio.h>

struct complex add(struct complex n1, struct complex n2);

struct complex{
    float real;
    float imag;
} complex;

int main (void)
{
    struct complex n1, n2, ans;

    scanf("%f %f", &n1.real, &n1.imag);
    scanf("%f %f", &n2.real, &n2.imag);

    ans = add(n1, n2);

    printf("Sum = %f + %fi\n", ans.real, ans.imag);

    return 0;
}

struct complex add(struct complex n1, struct complex n2)
{
    struct complex res;

    res.real = n1.real + n2.real;
    res.imag = n1.imag + n2.imag;

    return res;
}