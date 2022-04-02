#include <stdio.h>

void pascal(int level, long long int tri[][100]);

int main(void)
{
	int level;
	long long int tri[100][100];

	scanf("%d", &level);

	pascal(level, tri);

	for(int i = 0; i < level; i++) {
		for(int j = 0; j <= i; j++)
			printf("%lli ", tri[i][j]);
		printf("\n");
	}

	return 0;
}

void pascal(int level, long long int tri[][100])
{
	tri[0][0] = 1;
	tri[1][0] = 1;
	tri[1][1] = 1;

	for(int i = 2; i < level; i++) {
		tri[i][0] = 1;
		for(int j = 1; j < level-1; j++)
			tri[i][j] = tri[i-1][j-1] + tri[i-1][j]; 
		tri[i][i] = 1;
	}
}
