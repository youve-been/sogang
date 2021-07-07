#include <stdio.h>

void main()
{
	int num, cutline;
	int sum = 0;
	int i = 0;
	float avg;
	int count = 0;

	printf("Number of class : ");
	scanf("%d", &num);
	printf("Cutline : ");
	scanf("%d", &cutline);

	while(i<num)
	{
	  int score;
	  printf("Input score #%d : ", i);
	  scanf("%d", &score);
	  
	  if (score<cutline){
	    count++;
	  }
	  sum += score;
	  i++;
	}
	
	avg = (float)sum / num;

	printf("Average score : %.2f\n", avg);
	printf("Number of failures : %d\n", count);
}
