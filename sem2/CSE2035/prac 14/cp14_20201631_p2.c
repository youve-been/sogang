#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float coef;
    int expon;
} poly;

poly *poly_sum(int n, int m, poly *a, poly *b);

int main(void)
{
    int n, m;
    poly *a, *b, *ans;

    scanf("%d %d", &n, &m);
    a = (poly*)malloc(sizeof(poly)*n);
    b = (poly*)malloc(sizeof(poly)*m);
    ans = (poly*)malloc(sizeof(poly)*(n+m));

    for(int i = 0; i < n; i++) {
        scanf("%f", &a[i].coef);
        scanf("%d", &a[i].expon);
    }
    for(int i = 0; i < m; i++) {
        scanf("%f", &b[i].coef);
        scanf("%d", &b[i].expon);
    }

    ans = poly_sum(n, m, a, b);

    for(int i = 0; i < n+m; i++) {
        if((ans[i].expon == 0)&&(i != 0))
            break;
        if((i != 0)&&(ans[i].coef > 0))
            printf("+");
        if(ans[i].expon == 0) {
            printf("%.2f", ans[i].coef);
            continue;
        }
        printf("%.2fx^%d", ans[i].coef, ans[i].expon);
    }
    printf("\n");
    
    return 0;
}

poly *poly_sum(int n, int m, poly *a, poly *b)
{
    int i = 0;
    int j = 0;
    int index = 0;
    poly *ans;

    ans = (poly*)malloc(sizeof(poly)*(n+m));

    while((i<n)&&(j<m)) {
        if(a[i].expon < b[j].expon) {
            ans[index].expon = a[i].expon;
            i++;
        }
        else if(a[i].expon > b[j].expon){
            ans[index].expon = b[j].expon;
            j++;
        }
        else {
            ans[index].expon = a[i].expon;
            i++;
            j++;
        }
        index++;
    }

    if((i>=n)&&(j<m)){
        while(j<m) {
            ans[index].expon = b[j].expon;
            j++;
            index++;
        }
    }
    else if((i<n)&&(j>=m)) {
        while(i<n) {
            ans[index].expon = a[i].expon;
            i++;
            index++;
        }
    }

    for(index = 0, i = 0, j = 0; (i<n)||(j<m); index++) {
        ans[index].coef = 0;
        
        if(i<n) {
            if(a[i].expon == ans[index].expon) {
                ans[index].coef += a[i].coef;
                i++;
            }
        }
        if(j<m) {
            if(b[j].expon == ans[index].expon) {
                ans[index].coef += b[j].coef;
                j++;
            }
        }
    }

    return ans;
}