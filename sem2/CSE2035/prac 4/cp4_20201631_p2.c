#include <stdio.h>

void swap(int *a, int *b);
void sort(int *a, int m);
void all_sort(int a[][100], int n, int m);
int binary_search(int *a, int *endPtr, int key, int **findPtr);
int all_binary_search(int a[][100], int n, int m, int key, int **findPtr);

int main(void)
{
	int n, m, k;
	int a[100][100];
	int *endPtr;
	int **findPtr = &endPtr;
	int ans;

	scanf("%d %d %d", &n, &m, &k);

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++)
			scanf("%d", *(a+i)+j);
	}

	all_sort(a, n, m);
	ans = all_binary_search(a, n, m, k, findPtr);

	printf("%d\n", ans);
	if(ans == 1)
		printf("%p\n", *findPtr);
}

void swap(int *a, int *b)
{
	int temp;

	temp = *b;
	*b = *a;
	*a = temp;
}

void sort(int *a, int m)
{
	int minIndex;
	int i, j;

	for(i = 0; i < m-1; i++) {
		minIndex = i;
		for(j = i + 1; j < m; j++) {
			if(*(a+j)<*(a+minIndex))
				minIndex = j;
		}
		swap(a+i, a+minIndex);
	}
}

void all_sort(int a[][100], int n, int m)
{
	for(int i = 0; i < n; i++)
		sort(*(a+i), m);
}

int binary_search(int *a, int *endPtr, int key, int **findPtr)
{
	int *firstPtr;
	int *midPtr;
	int *lastPtr;

	firstPtr = a;
	lastPtr = endPtr;

	while(firstPtr <= lastPtr) {
		midPtr = firstPtr + (lastPtr - firstPtr) / 2;
		if(key > *midPtr)
			firstPtr = midPtr + 1;
		else if(key < *midPtr)
			lastPtr = midPtr - 1;
		else
			firstPtr = lastPtr + 1;
	}

	*findPtr = midPtr;
	return (key == *midPtr);
}

int all_binary_search(int a[][100], int n, int m, int key, int **findPtr)
{
    int ans;
	for(int i = 0; i < n; i++) {
		ans = binary_search(*(a+i), (*(a+i)+m-1), key, findPtr);
		if(ans == 1)
		    return 1;
	}
	
	return 0;
}
