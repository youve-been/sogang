#include <stdio.h>

void func(int arr[], int n, int res[][1000]);

int main(void)
{
	int n;
	int arr[1000];
	int res[1000][1000];

	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	func(arr, n, res);

	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= i; j++)
			printf("%d ", res[i][j]);
		printf("\n");
	}

	return 0;
}

void func(int arr[], int n, int res[][1000])
{
	for(int i = 0; i < n; i++)
		res[n-1][i] = arr[i];

	for(int i = n-2; i >= 0; i--) {
		for(int j = n-2; j >= 0; j--) {
			if(res[i+1][j] > res[i+1][j+1])
				res[i][j] = res[i+1][j+1];
			else
				res[i][j] = res[i+1][j];
		}
	}
}
