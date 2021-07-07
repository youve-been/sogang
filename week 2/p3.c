#include <stdio.h>

void main()
{
	int a, b;

	printf("input two integer : ");
	scanf("%d %d", &a, &b);

	printf("%d / %d is %d with a remainder of %d\n", a, b, a/b, a%b);
}

