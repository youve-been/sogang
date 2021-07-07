#include <stdio.h>

void Calc_PlusOne (int sum, int a, int b);
int Calc (int sum, int a, int b);

int count = 0;

void main()
{
	int a, b;

	printf("Enter 2 number : ");
	scanf("%d %d", &a, &b);
	
	Calc(a+b,a,b);

	printf("%d carry operations\n", count);
}

int Calc (int sum, int a, int b)
{
	if (sum == 0){
		return 0;
	}
	else{
		if (sum%10 != ((a%10) + (b%10))) {
			count += 1 ;
			Calc_PlusOne(sum/10, a/10, b/10);
		}
		else{
			Calc(sum/10, a/10, b/10);
		}
	}
}

void Calc_PlusOne (int sum, int a, int b)
{
	if (sum%10 != ((a%10)+(b%10)+1)) {
		count += 1 ;
		Calc_PlusOne(sum/10, a/10, b/10);
	}
	else {
		Calc(sum/10, a/10, b/10);
	}
}
