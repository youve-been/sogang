#include <stdio.h>

void main()
{
	int a;

	printf("input a : ");
	scanf("%d", &a);
	printf("a = %d\n", a);

	a++;
	printf("a = a + 1; a = %d\n", a++);
	printf("a = a + 1; a = %d\n", a);

	a--;
	printf("a = a - 1; a = %d\n", a);
}

