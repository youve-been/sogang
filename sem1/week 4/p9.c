#include <stdio.h>

void divideRemainder(int * a, int * b);

void main()
{
	int a, b;

	printf("Input two Number : ");
	scanf("%d %d", &a, &b);

	divideRemainder(&a, &b);

	printf("---------------------------------------------\n");
	printf("OUTPUT : divide [%d] remainder [%d]\n", a, b);
}

void divideRemainder(int* a, int* b)
{
	int q, r;

	q = *a / *b;
	r = *a % *b;

	*a = q;
	*b = r;
}
