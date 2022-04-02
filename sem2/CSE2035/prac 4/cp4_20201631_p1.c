#include <stdio.h>

void swap(int *a, int *b);
void make_array(int *a, int *b, int n, int k);
void check_array(int *a, int *b, int n);
void print_array(int *a, int n);

int main(void)
{
	int n;
	int a[8], b[8];

	scanf("%d", &n);

	for(int i = 0; i < n; i++)
		scanf("%d", a+i);

	for(int i = 0; i < n; i++)
		*(b+i) = *(a+i);

	make_array(a, b, n, 0);

	return 0;
}

void swap(int *a, int *b)
{
	int temp;

	temp = *b;
	*b = *a;
	*a = temp;
}

void make_array(int *a, int *b, int n, int k)
{
	if(k == n) {
		check_array(a, b, n);
		return;
	}

	for(int i = k; i < n; i++) {
		swap(a+i, a+k);
		make_array(a, b, n, k+1);
		swap(a+i, a+k);
	}
}

void check_array(int *a, int *b, int n)
{
	int k = 0;

	for(int i = 0; i < n; i++) {
		if(*(a+i) == *(b+i))
			k = 1;
	}

	if(k == 0)
		print_array(a, n);
}

void print_array(int *a, int n)
{
	for(int i = 0; i < n; i++)
		printf("%d ", *(a+i));
	printf("\n");
}
