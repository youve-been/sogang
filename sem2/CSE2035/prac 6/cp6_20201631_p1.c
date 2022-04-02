#include <stdio.h>
#include <stdlib.h>

void fiv(int *p, int n);

int main(void)
{
	int n;
	int *p;

	scanf("%d", &n);

	p = (int *)malloc(n*sizeof(int));

	fiv(p, n);

	for(int i = 0; i < n; i++)
		printf("%d ", *(p+i));
	printf("\n");

	return 0;
}

void fiv(int *p, int n)
{
	*p = 1;
	*(p+1) = 1;

	for(int i = 2; i < n; i++)
		*(p+i) = *(p+i-1) + *(p+i-2);
}
