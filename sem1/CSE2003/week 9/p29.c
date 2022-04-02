#include <stdio.h>

float Average(int mat[][100], int col, int n); 

void main()
{
	int n;
	int matrix[100][100];
	char input[200];

	scanf("%d",&n);

	for(int i = 0; i <= n ; i++) {
		for(int k = 0; k<200; k++) {
			scanf("%c", &input[k]);
			if(input[k] == '\n')
				break;
		}
		for (int j = 0; j< n; j++)
			matrix[i][j] = input[j*2]-48;
	}

	for(int i = 1; i<=n; i++) {
		printf("%.2f ", Average(matrix, i, n));
	}
	printf("\n");
}

float Average(int mat[][100], int col, int n)
{
	float sum = 0;

	for(int i = 1; i<= n; i++)
		sum += mat[i][col];

	sum /= n;

	return sum;
}
