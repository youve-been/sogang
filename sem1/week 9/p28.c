#include <stdio.h>

void Capital(char arr[]);

void main()
{
	char sentence[50];

	for (int i = 0; i<50; i++)
		scanf("%c", &sentence[i]);

	Capital (sentence);

	for (int i = 0; i<50; i++)
		printf("%c", sentence[i]);
	printf("\n");
}	

void Capital(char arr[])
{
	for (int i = 0; i<50; i++)
	{
		if(arr[i]>=97 && arr[i]<=122)
			arr[i] -= 32;
	}
}
