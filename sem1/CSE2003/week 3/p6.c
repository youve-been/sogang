#include <stdio.h>

int Add(int a, int b);

void main()
{
	int a, b;
	int total;

	printf("Input first number : ");
	scanf("%d", &a);
	printf("Input second number : ");
	scanf("%d", &b);

	total = Add(a,b);

	printf("%d + %d = %d\n", a, b, total);
}

int Add(int a, int b)
{
	int total;

	total = a + b;

	return total;
}

