#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int n, m, max, temp = 0;
	int *p1, *p2, *sum;
	int i, j, k;

	scanf("%d %d", &n, &m);

	if(n>m)
		max = n+1;
	else
		max = m+1;

	p1 = (int *)malloc(n*sizeof(int));
	p2 = (int *)malloc(m*sizeof(int));
	sum = (int *)malloc(max*sizeof(int));

	for(int x = n-1; x >= 0; x--)
		scanf("%1d", p1+x);
	for(int y = m-1; y >= 0; y--)
		scanf("%1d", p2+y);

	for(i = 0, j = 0, k = 0; k < max; i++, j++, k++) {
		if(i >= n)
			*(p1+i) = 0;
		if(j >= m)
			*(p2+j) = 0;

		*(sum+k) = *(p1+i) + *(p2+j) + temp;
		temp = *(sum+k) / 10;
		*(sum+k) %= 10;
	}

	for(int x = max-1; x >= 0; x--) {
		if((x == max-1)&&(*(sum+x) == 0))
			continue;
		printf("%d", *(sum+x));
	}
	printf("\n");

	return 0;
}
