#include <stdio.h>

void shift_n_left(int *a, int n);
void shift_n_right(int *a, int n);
void print_array(int *a);

int main()
{
	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int n, way;

	scanf("%d", &n);
	scanf("%d", &way);

	if(way == 0)
		shift_n_left(a, n);
	else
		shift_n_right(a, n);

	print_array(a);

	return 0;
}

void shift_n_left(int *a, int n)
{
	int tmp[10] = {0};

	for(int i = 0; i < n; i++)
		*(tmp + (i+10-n)) = *(a + i);

	for(int i = n; i < 10; i++)
		*(a + (i-n)) = *(a + i);

	for(int i = 10-n; i < 10; i++)
		*(a + i) = *(tmp + i);
}

void shift_n_right(int *a, int n)
{
	int tmp[10] ={0};

	for(int i = 9; i > 9 - n; i--)
		*(tmp + (i-10+n)) = *(a + i);

	for(int i = 9-n; i >= 0; i--)
		*(a + (i+n)) = *(a + i);

	for(int i = 0; i < n; i++)
		*(a + i) = *(tmp + i);
}

void print_array(int *a)
{
	for(int i = 0; i < 10; i++)
		printf("%d ", *(a + i));
	printf("\n");
}
