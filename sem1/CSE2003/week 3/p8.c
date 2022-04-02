#include <stdio.h>

float average(int a, int b, int c, int d);
float deviation(float avg, int a);

void main()
{
	int a, b, c, d;
	float avg;
	float dev_a, dev_b, dev_c, dev_d;

	printf("Enter the first number : ");
	scanf("%d", &a);
	printf("Enter the second number : ");
	scanf("%d", &b);
	printf("Enter the third number : ");
	scanf("%d", &c);
	printf("Enter the fourth number : ");
	scanf("%d", &d);

	avg = average(a, b, c, d);
	dev_a = deviation(avg, a);
	dev_b = deviation(avg, b);
	dev_c = deviation(avg, c);
	dev_d = deviation(avg, d);

	printf("********** average is %.2f **********\n", avg);
	printf("first number :  %20d  -- deviation : %20.2f\n", a, dev_a);
	printf("second number : %20d  -- deviation : %20.2f\n", b, dev_b);
	printf("thrid number :  %20d  -- deviation : %20.2f\n", c, dev_c);
	printf("fourth number : %20d  -- deviation : %20.2f\n", d, dev_d);
}

float average(int a, int b, int c, int d)
{
	float avg;

	avg = ((float)a + b + c + d) / 4;

	return avg;
}

float deviation(float avg, int a)
{
	float dev;

	dev = a - avg;

	return dev;
}
