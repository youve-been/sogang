#include <stdio.h>

void f(int *Y, int *M, int *D, int X);

int main(void)
{
	int Y = 2020;
	int M = 9;
	int D = 0;
	int X;

	scanf("%d", &X);

	f(&Y, &M, &D, X);

	printf("%04d년 %02d월 %02d일\n", Y, M, D);

	return 0;
}

void f(int *Y, int *M, int *D, int X)
{
	if(X<21) {
		*D += X + 10;
		return;
	}
	X -= 20;
	(*M)++;

	if(X<32) {
		*D += X;
		return;
	}
	X -= 31;
	(*M)++;

	if(X<31) {
		*D += X;
		return;
	}
	X -= 30;
	(*M)++;

	if(X<32) {
		*D += X;
		return;
	}
	X -= 31;
	*Y += 1;
	*M = 1;

	if(X<32) {
		*D += X;
		return;
	}
	X -= 31;
	(*M)++;

	if(X<29) {
		*D += X;
		return;
	}
	X -= 28;
	(*M)++;

	if(X<32) {
		*D += X;
		return;
	}
	X -= 31;
	(*M)++;

	if(X<31) {
		*D += X;
		return;
	}
	X -= 30;
	(*M)++;

	if(X<32) {
		*D += X;
		return;
	}
	X -= 31;
	(*M)++;

	if(X<31) {
		*D += X;
		return;
	}
	X -= 30;
	(*M)++;

	if(X<32) {
		*D += X;
		return;
	}
	X -= 31;
	(*M)++;

	if(X<32) {
		*D += X;
		return;
	}
	X -= 31;
	(*M)++;

	*D += X;
	return;
}
