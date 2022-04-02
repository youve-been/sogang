#include <stdio.h>

void swap(int *a, int *b);
void sort(int *a, int n);
void print_array(int *a, int n);

int main(void)
{
	int n;
	int num[1000];

	scanf("%d", &n);

	for(int i = 0; i < n; i++)
		scanf("%d", num+ i*4);

	sort(num, n);
	print_array(num, n);

	return 0;
}

void swap(int *a, int *b)
{
	int temp;

	temp = *b;
	*b = *a;
	*a = temp;
}

void sort(int *a, int n)
{
	int i, j, key;

	for(i = 1; i < n; i++) {
		key = *(a + 4*i);
		for(j = i-1; (j>=0) && (*(a+j*4)>key);j--)
			*(a + (j+1)*4) = *(a + j*4);
		*(a + (j+1)*4) = key;
	}
}

void print_array(int *a, int n)
{
	for(int i = 0; i < n; i++)
		printf("%d ", *(a+i*4));

	printf("\n");
}
