#include <stdio.h>

void main()
{
	float a, b;

	printf("Input : ");
	scanf("%f", &a); 

	b = a + 0.51;

	printf("Use \">\" : %d\n", ((int)b-(int)a) > 0.9 );
	printf("Use \">=\" : %d\n", ((int)b-(int)a) >= 1);
	printf("Use \"==\" : %d\n", 1 ==((int)b-(int)a));
	printf("Use \"!=\" : %d\n", 0 != ((int)b-(int)a));
}
