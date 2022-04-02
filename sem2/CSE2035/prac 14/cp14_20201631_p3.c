#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float coef;
    int expon;
} poly;

poly *poly_integral(int n, poly *a);
poly *poly_derivative(int n, poly *a);

int main(void)
{
    poly *a, *inte, *deri;
    int n;

    scanf("%d", &n);
    a = (poly *)malloc(sizeof(poly)*n);
    for(int i = 0; i < n; i++)
        scanf("%f %d", &a[i].coef, &a[i].expon);
    
    inte = (poly *)malloc(sizeof(poly)*(n+1));
    deri = (poly *)malloc(sizeof(poly)*n);

    inte = poly_integral(n, a);
    deri = poly_derivative(n, a);

    printf("Integral : ");
    for(int i = 0; i <= n; i++) {
        if((inte[i].expon == 0)&&(i != 0))
            break;
        if((i != 0)&&(inte[i].coef > 0))
            printf("+");
        if(inte[i].expon == 0) {
            printf("%.2f", inte[i].coef);
            continue;
        }
        printf("%.2fx^%d", inte[i].coef, inte[i].expon);
    }
    printf("\n");

    printf("Derivative : ");
    for(int i = 0; i < n; i++) {
        if((deri[i].expon == 0)&&(deri[i].coef == 0))
            continue;
        if((i != 0)&&(deri[i].coef > 0))
            printf("+");
        if((deri[i].expon == 0)&&(deri[i].coef != 0)) {
            printf("%.2f", deri[i].coef);
            continue;
        }
        printf("%.2fx^%d", deri[i].coef, deri[i].expon);
    }
    printf("\n");

    return 0;
}

poly *poly_integral(int n, poly *a)
{
    poly *ans;

    ans = (poly*)malloc(sizeof(poly)*(n+1));

    for(int i = 0; i < n; i++) {
        ans[i].expon = a[i].expon + 1;
        ans[i].coef = a[i].coef/(a[i].expon+1);
    }

    for(int i = 0; i < n; i++) {
        if(ans[i].expon == 0) {
            a[i].coef++;
            break;
        }
        else if(((ans[i-1].expon<0)&&(ans[i].expon>0))||(ans[0].expon>0)) {
            for(int j = n; j > i; j--) {
                ans[j].expon = ans[j-1].expon;
                ans[j].coef = ans[j-1].coef; 
            }
            ans[i].expon = 0;
            ans[i].coef = 1;
            break;
        }
    }

    return ans;
}

poly *poly_derivative(int n, poly *a)
{
    poly *ans;

    ans = (poly *)malloc(sizeof(poly)*n);

    for(int i = 0; i < n; i++) {
        if(a[i].expon == 0)
            continue;
        ans[i].coef = a[i].coef * a[i].expon;
        ans[i].expon = a[i].expon - 1;
    }

    return ans;
}