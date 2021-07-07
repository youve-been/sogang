#include <stdio.h>

int Age(int y, int year);

void main()
{
	int birthday;
	int y, m, d;
	int year, age;

	printf("Birthday : ");
	scanf("%d", &birthday);

	y = birthday / 10000;
	m = birthday / 100 - y * 100;
	d = birthday - y * 10000 - m * 100;

	printf("Your birthday is %d / %d / %d\n", y, m, d);

	printf("Year : ");
	scanf("%d", &year);

	age =  Age(y, year);

	printf("In %d, your age is %d\n", year, age);
}

int Age(int y, int year)
{
	int age;

	age = year - y + 1;

	return age;
}

