#include <stdio.h>

void *f(void *pa, void *pb, int option);

int main(void)
{
	int option;
	int a, b;
	float fa, fb;
	double da, db;
	void *pa, *pb, *ans;

	scanf("%d", &option);

	switch (option) {
		case 0:
			scanf("%d %d", &a, &b);
			pa = &a;
			pb = &b;
			ans = f(pa, pb, option);
			printf("%d\n", *(int *)ans);
			break;
		case 1:
			scanf("%f %f", &fa, &fb);
			pa = &fa;
			pb = &fb;
			ans = f(pa, pb, option);
			printf("%f\n", *(float *)ans);
			break;
		case 2:
			scanf("%lf %lf", &da, &db);
			pa = &da;
			pb = &db;
			ans = f(pa, pb, option);
			printf("%lf\n", *(double *)ans);
			break;
		default:
			break;
	}

	return 0;
}

void *f(void *pa, void *pb, int option)
{
	void *ans;

	if (option == 0) {
		if(*(int *)pa > *(int *)pb)
			ans = pb;
		else
			ans = pa;
	}
	else {
		if(*(double *)pa > *(double *)pb)
			ans = pb;
		else
			ans = pa;
	}

	return ans;	
}
