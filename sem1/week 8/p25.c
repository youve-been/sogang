#include <stdio.h>

int palindrome (int num, int digit);

int main(void) {
	int num;

	printf("Input : ");	
	scanf("%d", &num);
	
	if (num>=0) {
		if (palindrome(num, 1) == 1)
			printf("%d is a palindrome number.\n", num);
		else
			printf("%d is not a palindrome number.\n", num);
	}
	else
		printf("Input number cannot be negative.\n");
}

int palindrome (int num, int digit) 
{
	int num1 = 0;
	int x, y;
	int i;
	
	if (num / digit != 0) {
		for (int temp = num; temp>0; num1 *= 10 ) {
			int i;
			
			i = temp % 10;
			temp /= 10;
			num1 += i;
		}
		num1 /= 10;
	
		x = num % (digit*10);
		y = num1 % (digit*10);
		
		if (x == y)
			i = palindrome (num, digit*10);
		else
			i = 0;
	}
	else
		i = 1;
	
	return i;
}
