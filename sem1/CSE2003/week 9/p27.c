#include <stdio.h>

void swap (int* a, int *b);

void main()
{
	int num[10];
	int max, min;

	printf("Input (10 numbers) : ");
	for (int i = 0; i < 10; i++)
		scanf("%d", &num[i]);

	max = num[0];
	min = num[0];

	for (int i = 0; i<5; i++) 
		swap(&num[i], &num[9-i]);

	for (int i = 0; i<10; i++) {
		if (max<num[i])
			max = num[i];
		if (min>num[i])
			min = num[i];
	}

	for (int i = 0; i<10; i++)
		printf("%d ", num[i]);
	printf("\n");

	printf("Max : %d, Min : %d\n", max, min);
}

void swap(int* a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
