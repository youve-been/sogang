#include <stdio.h>

void func(int arr[], int n, int psum[][1000]);

int main(void)
{
	int n;
	int arr[1000];
	int a, b;
	int psum[1000][1000];

	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	scanf("%d %d", &a, &b);

	func(arr, n, psum);

	printf("%d\n", psum[a][b]);

	return 0;
}

void func(int arr[], int n, int psum[][1000])
{
	int sum = 0;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i<j)
				psum[i][j] = 0;
			for(int k = i; k <= j; k++)
				sum += arr[k];
			psum[i][j] = sum;
			sum = 0;
		}
	}
}
