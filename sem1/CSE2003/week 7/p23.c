#include <stdio.h>

void func_gcd(int a, int b, int* gcd);

void main()
{
	int a, b;
	int gcd;

	printf("Input first number : ");
	scanf("%d", &a);
	printf("Input second number : ");
	scanf("%d", &b);

	func_gcd(a, b, &gcd);

	printf("GCD : %d\n", gcd);
}

void func_gcd(int a, int b, int* gcd)
{
	int x, y;

	do{
	  y = a % b;
	
	  if (y == 0)
	    break;
	  else { 
	    a = b;
	    b = y;
	  }
	} while (b > 0);

	*gcd = b;
}
