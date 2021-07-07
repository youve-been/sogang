#include <stdio.h>

int Change(int a);

void main()
{
	int a;

	scanf("%d", &a);

	a = Change(a);

	printf("%d\n",a);
}

int Change (int a)
{
	int x = 0;

	do{
	  x = x * 10;
	  x += (a % 10);
	  a = a / 10;
	} while (a);
	
	return x;
}
