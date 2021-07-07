#include <stdio.h>

void main()
{
	int step;
	int i;
	int count;
	int j=0;

	printf("Input : ");
	scanf("%d", &step);
	
	while (step)
	{
	  i = 1;
	  count = 0;
	  while (i<step)
	  {
	    printf(" ");
	    i++;
	  }
	  while (count<(2*j+1))
	  {
	    printf("*");
	    count++;
	  }
	  printf("\n");
	  step--;
	  j++;
	}
}
