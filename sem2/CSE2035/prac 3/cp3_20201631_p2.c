#include <stdio.h>

void make_array(int *a, int *b, int n);
void print_array(int *a, int n);

int main(void)
{
	int n;
	int a[10];
	int b[10];

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", a+i);

	make_array(a, b, n);

	print_array(b, n);

	return 0;
}

void make_array(int *a, int *b, int n)
{
	*b = *(a+n-1);

	for(int i = n; i > 0; i--)
		*(b + i) = *(a + i-1);
}

void print_array(int *a, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", *(a+i));
	printf("\n");
}
