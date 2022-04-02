#include <stdio.h>

int k = 1;

void right(int arr[][20], int x, int n);
void down(int arr[][20], int x, int n);
void left(int arr[][20], int x, int n);
void up(int arr[][20], int x, int n);

int main(void) {
	int n;
	int snail[20][20] = {0};
	int temp;
	int x;
	
	printf("Input : ");
	scanf("%d", &n);

    for( ; n; n--) {
        temp = n;
        k = 1;
        
    	for (x = 0; x < n; x++) {
    		right(snail, x, temp);
    		down(snail, x, temp);
    		left(snail, x, temp);
    		up(snail, x, temp);
    		temp--;
    		
    		if(k > n*n)
    			break;
    	}
    
    	for(int i = 0; i < n; i++) {
    		for(int j = 0; j < n; j++)
		    	printf("%3d", snail[i][j]);
	    	printf("\n");
    	}
    	
    	printf("\n");
    }
	
	return 0;
}

void right(int arr[][20], int x, int n)
{
    for(int i = 0; i < n-x; i++) {
		arr[x][i+x] = k;
		k++;
	}
	k--;
}

void down(int arr[][20], int x, int n)
{
	for(int i = 0; i < n-x; i++) {
		arr[i+x][n-1] = k;
		k++;
	}
	k--;
}
void left(int arr[][20], int x, int n)
{
	for(int i = 0; i < n-x; i++) {
		arr[n-1][n-i-1] = k;
		k++;
	}
	k--;
}
void up(int arr[][20], int x, int n)
{
	for(int i = 0; i < n-1-x; i++) {
		arr[n-i-1][x] = k;
		k++;
	}
}