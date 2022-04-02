#include <stdio.h>

void fourMath (int *c, int *d);
void printResult (int *c,int *d);

int a, b;

void main()
{
	int a, b;

	printf("Input two number : ");
	scanf("%d %d", &a, &b);

	fourMath(&a, &b);

	printResult(&a, &b);
}

void fourMath (int *c, int *d)
{
	a = *c * *d;
	b = *c / *d;
	*c = *c + *d;
	*d = *c - *d - *d;
}

void printResult (int *c, int *d)
{
	printf("Result : a+b = %d, a-b = %d, a*b = %d, a/b = %d\n", *c, *d, a, b);
} 
