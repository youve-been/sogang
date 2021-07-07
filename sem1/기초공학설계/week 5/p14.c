#include <stdio.h>

void Find_LeapYear (int y);

void main()
{
	int year;

	printf("Enter the year to be tested : ");
	scanf("%d", &year);

	if ((((year%4) == 0) && (year%100 !=0))||((year%400) == 0)){
		printf("It is a leap year\n");
	}
	else {
	printf("It is not a leap year\n");
	Find_LeapYear(year-1);
	}
}

void Find_LeapYear(int y)
{
	int leap_year;

	if ((((y%4) == 0) && (y%100 !=0))||((y%400) == 0)){
		leap_year = y;
		printf("%d is a leap year\n", leap_year);
	}
	else {
		Find_LeapYear(y-1);
	}

}
