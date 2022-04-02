#include <stdio.h>

double calc(int *a, int n);

int main(void)
{
	int n;
	int num[10000];
	double avg;

	scanf("%d", &n);

	for(int i = 0; i < n; i++)
		scanf("%d", num + i*4);

	avg = calc(num, n);

	printf("%.2lf\n", avg);

	return 0;
}

double calc(int *a, int n)
{
	double avg;

	for(int i = 0; i < n; i++)
		avg += *(a + i*4);

	avg /= n;

	return avg;
}
