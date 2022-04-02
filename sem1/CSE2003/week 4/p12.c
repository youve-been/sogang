#include <stdio.h>

int Fibonacci (int *y);

int x = 0;

void main()
{
	int x = 1;

	x = Fibonacci(&x);
	printf("Fibo(2) : %d\n", x);
	
	x = Fibonacci(&x);
	printf("Fibo(3) : %d\n", x);
	
	x = Fibonacci(&x);
	printf("Fibo(4) : %d\n", x);

	x = Fibonacci(&x);
	printf("Fibo(5) : %d\n", x);

	x = Fibonacci(&x);
	printf("Fibo(6) : %d\n", x);

	x = Fibonacci(&x);
	printf("Fibo(7) : %d\n", x);

	x = Fibonacci(&x);
	printf("Fibo(8) : %d\n", x);

	x = Fibonacci(&x);
	printf("Fibo(9) : %d\n", x);
}

int Fibonacci (int *y)
{
	int temp;

	temp = x + *y;
	x = *y;

	return temp;
}
