#include <stdio.h>

void sqr(int a);
void printOne(int a_sqr);

void main()
{
	int a;

	printf("Input : ");
	scanf("%d", &a);

	sqr(a);
}

void sqr(int a)
{
	int a_sqr;
	
	a_sqr = a * a;

	printOne(a_sqr);
}

void printOne(int a_sqr)
{
	printf("Result : %d\n", a_sqr);
}

