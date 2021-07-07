#include <stdio.h>

int isDivisor(int m, int n);
int isPrime(int m);

void main()
{
	int num;

	printf("Input : ");
	scanf("%d", &num);

	if (isDivisor(num, 2) == 1)
	  printf("2\t");
	for (int i = 2; i <= num; i++){
	  if(isDivisor(num, i) == 1)
	    if(isPrime(i) == 1)
	      printf("%d\t", i);
	}
	printf("\n");
}

int isDivisor(int m, int n)
{
	int i;

	if(m%n == 0)
	  i = 1;
	else
	  i = 0;

	return i;
}

int isPrime(int m)
{
	int x;

	for(int i = 2; i < m; i++) {
	  if (m % i == 0) {
	    x = 0;
	    break;
	  }
	  else
	    x = 1;
	}

	return x;
}
