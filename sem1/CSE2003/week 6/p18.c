#include <stdio.h>

void dec2oct(int* a, int* b, int* c, int* d, int num);
void dec2hex(char* a, char* b, char* c, int num);
char digit2hex(int a);

void main()
{
	int num;
	int oct1, oct2, oct3, oct4;
	char hex1, hex2, hex3;

	scanf("%d", &num);

	dec2oct(&oct1, &oct2, &oct3, &oct4, num);
	dec2hex(&hex1, &hex2, &hex3, num);

	printf("%04o\n", num);
	printf("%d%d%d%d\n", oct1, oct2, oct3, oct4);
	printf("%03X\n", num);
	printf("%c%c%c\n", hex1, hex2, hex3);
}

void dec2oct(int* a, int*b, int*c, int* d, int num)
{
	*a = num/512;
	*b = (num % 512)/64;
	*c = (num % 64)/8;
	*d = num%8;
}

void dec2hex(char* a, char* b, char* c, int num)
{
	int x, y, z;

	x = num/256;
	y = (num % 256)/16;
	z = num%16;

	*a = digit2hex(x);
	*b = digit2hex(y);
	*c = digit2hex(z);
}

char digit2hex(int a)
{
	char hex;

	if (a<10)
	  hex = a + 48;
	else
	  hex = a + 55;

	return hex;
}
