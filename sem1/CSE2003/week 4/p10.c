#include <stdio.h>

void swap(float * x, float * y);

void main()
{
	float x, y;

	printf("Input two Number\n");
	printf("\tx : ");
	scanf("%f", &x);
	printf("\ty : ");
	scanf("%f", &y);

	printf("-----------------------------------------\n");
	printf("Before : x [%g] y [%g]\n", x, y);

	swap(&x, &y);

	printf("-----------------------------------------\n");
	printf("After  : x [%g] y [%g]\n", x, y);

}

void swap(float * x, float * y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
