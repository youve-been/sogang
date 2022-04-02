#include <stdio.h>

int main(void)
{
	int a, b, c;
	int *pa, *pb, *pc;
	int *max, *min;

	scanf("%d %d %d", &a, &b, &c);

	pa = &a;
	pb = &b;
	pc = &c;

	if(*pa>*pb) {
		if(*pb>*pc) {
			max = pa;
			min = pc;
		}
		else {
			min = pb;
			max = *pa > *pc ? pa : pc;
		}
	}
	else {
		if(*pa>*pc) {
			max = pb;
			min = pc;
		}
		else {
			min = pa;
			max = *pb > *pc ? pb : pc;
		}
	}

	printf("%d %d\n", *min, *max);
	printf("%p %p\n", min, max);

	return 0;
} 
