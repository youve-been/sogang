#include <stdio.h>
#include <stdlib.h>

int *fiv(int num);
int *Add(int *n, int *m, int *max, int *p1, int *p2, int *sum);

int main(void)
{
    int num;
	int *p;

	scanf("%d", &num);

	p = fiv(num);

	for(int i = 0; i < num; i++)
		printf("%d ", *(p+i));
	printf("\n");

	return 0;
}

int *fiv(int num)
{
    int *p1, *p2, *sum;
    int n, m, max;
    int *pn = &n;
    int *pm = &m;
    int *pmax = &max;

    p1 = (int *)malloc(sizeof(int));
    p2 = (int *)malloc(sizeof(int));
    sum = (int *)malloc(sizeof(int));
    
    n = 1;
    m = 1;
    max = 1;
    
    for(int i = 0; i < num; i++) {
        sum = Add(pn, pm, pmax, p1, p2, sum);
        
        p1 = (int *)realloc(p1, n * sizeof(int));
        p1 = p2;
        
        p2 = (int *)realloc(p2, m * sizeof(int));
        p2 = sum;
        
        sum = (int *)realloc(sum, max * sizeof(int));
    }
    
    return sum;
}

int *Add(int *n, int *m, int *max, int *p1, int *p2, int *sum)
{
	int temp = 0;
	int i, j, k;

	if(*n>*m)
		*max = *n+1;
	else
		*max = *m+1;

	for(i = 0, j = 0, k = 0; k < *max; i++, j++, k++) {
		if(i >= *n)
			*(p1+i) = 0;
		if(j >= *m)
			*(p2+j) = 0;

		*(sum+k) = *(p1+i) + *(p2+j) + temp;
		temp = *(sum+k) / 10;
		*(sum+k) %= 10;
	}
	
	*n = *m;
	*m = *max;

	return 0;
}