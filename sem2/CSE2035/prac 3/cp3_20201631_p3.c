#include <stdio.h>

void func(int a[100][100], int b[100][100], int c[100][100], int N, int op);

int main(void)
{
	int N;
	int a[100][100], b[100][100], c[100][100];
	int op;

	scanf("%d", &N);
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++)
			scanf("%d", (*(a+i)+j));
	}
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++)
			scanf("%d", (*(b+i)+j));
	}
	scanf("%d", &op);

	func(a, b, c, N, op);

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++)
			printf("%d ", *(*(c+i)+j));
		printf("\n");
	}
}

void func(int a[100][100], int b[100][100], int c[100][100], int N, int op)
{
	switch(op) {
		case 0:
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++)
					*(*(c+i)+j) = *(*(a+i)+j) + *(*(b+i)+j);
			}
			break;
		case 1:
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++)
					*(*(c+i)+j) = *(*(a+i)+j) - *(*(b+i)+j);
			}
			break;
		case 2:
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					for(int k = 0; k < N; k++)
						*(*(c+i)+j) += (*(*(a+i)+k)) * (*(*(b+k)+j));
				}
			}
			break;
	}
}
