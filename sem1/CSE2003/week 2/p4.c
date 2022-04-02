#include <stdio.h>

void main()
{
	int price;
	int a, b;
	int price_3, price_6;
	float price_month_3, price_month_6;

	a = 3;
	b = 6;

	printf("Price : ");
	scanf("%d", &price);

	price_3 = price;
	price_6 = (((float)price)*1.05*1.05*1.05);

	printf("----------------output----------------\n");
	printf("Month\t\t: %10d%10d\n", a, b);
	printf("Payment\t\t: %10d%10d\n", price_3, price_6);

	price_month_3 = (float)price_3/3;
	price_month_6 = (float)price_6/6;

	printf("--------------------------------------\n");
	printf("Pay/Month\t: %10.2f%10.2f\n", price_month_3, price_month_6);
}

