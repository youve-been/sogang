#include <stdio.h>

void calc(int *a, int *b, char op);

int main(void)
{
	int a, b;
	int *pa, *pb;
	char op;

	scanf("%c", &op);
	scanf("%d %d", &a, &b);

	pa = &a;
	pb = &b;
	calc(pa, pb, op);

	printf("%d\n", a);

	return 0;
}

void calc(int *a, int *b, char op)
{
	switch (op) {
		case '+':
			*a = *a + *b;
			break;
		case '-' :
			*a = *a - *b;
			break;
		case '*':
			*a = *a * *b;
			break;
		case '/':
			*a = *a / *b;
			break;
		default:
			break;
	}
}
