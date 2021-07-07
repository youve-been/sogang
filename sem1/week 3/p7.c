#include <stdio.h>

float find_x(int a, int b, int c, int d);
float find_y(int a, int b, float x);

void main()
{
	int a, b;
	int c, d;
	float x, y;

	printf("1st equation : y = ax - b, input 'a' and 'b'\n");
	printf("a = ");
	scanf("%d", &a);
	printf("b = ");
	scanf("%d", &b);

	printf("2nd equation : y = cx - d, input 'c' and 'd'\n");
	printf("c = ");
	scanf("%d", &c);
	printf("d = ");
	scanf("%d", &d);

	x = find_x(a, b, c, d);
	y = find_y(a, b, x);

	printf("result : \n");
	printf("x is %f\n", x);
	printf("y is %f\n", y);
}

float find_x(int a, int b, int c, int d)
{
	float x;

	x = ((float)b - d)/(a - c);

	return x;
}

float find_y(int a, int b, float x)
{
	float y;

	y = a * x - b;

	return y;

}

