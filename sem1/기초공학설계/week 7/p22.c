#include <stdio.h>

void swap(int* a, int* b);

int main(void)
{
	int a, b;
	int sum = 0;

	printf("Input first number : ");
	scanf("%d", &a);
	printf("Input second number : ");
	scanf("%d", &b);

	if (a<1 || b<1) {
	  printf("Input is less than 1\n");
	  return 0;
	}
	else {
	  if (a > b)
	    swap(&a, &b);

	  for (int i = a; i <= b; i++) {
	    if((i % 2 == 0) || (i % 3 == 0))
	      sum += i;
	  }
	} 

	printf("Result : %d\n", sum);
	return 0;
}

void swap(int* a, int* b)
{
	int temp;

	temp = *b;
	*b = *a;
	*a = temp;
}
