#include <stdio.h>

int avgFunc(float a, float  b, float  c);
char gradeFunc(int avg);

void main()
{
	float a, b, c;
	int avg;
	char grade;

	printf("Input : ");
	scanf("%f %f %f", &a, &b, &c);

	avg = avgFunc(a,b,c);
	grade = gradeFunc(avg);

	printf("Grade : %c\n", grade);
}

int avgFunc(float a, float b, float c)
{
	int avg;

	avg = (a+b+c)/3;

	return avg;
}

char gradeFunc(int avg)
{
	char grade;

	if(avg>=50)
	{
	  if(avg>=70)
	  {
	    if(avg>=80)
	    {
	      if(avg>=90)
	        grade = 'A';
	      else
	        grade = 'B';
	    }
	    else
	      grade = 'C';
	  }
	  else
	    grade = 'D';
	}
	if(avg<50)
	  grade = 'F';

	return grade;
}
