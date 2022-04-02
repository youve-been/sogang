#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union utemp {
    int i;
    float f;
    double d;
};

typedef struct {
    int type;
    char name[20];
    union utemp u;
} stemp;

void power(stemp *s);

int main(void)
{
    int n;
    stemp *num;

    printf("Number of Iterations : ");
    scanf("%d", &n);
    num = (stemp *)malloc(sizeof(stemp)*n);
    for(int i = 0; i < n; i++) {
        printf("Type [1 for int, 2 for float, 3 for double] : ");
        scanf("%d", &num[i].type);
        switch(num[i].type) {
            case 1 :
                strcpy(num[i].name, "integer");
                printf("Enter an integer value : ");
                scanf("%d", &num[i].u.i);
                break;
            case 2 : 
                strcpy(num[i].name, "float");
                printf("Enter an float value : ");
                scanf("%f", &num[i].u.f);
                break;
            case 3 :
                strcpy(num[i].name, "double");
                printf("Enter an double value : ");
                scanf("%lf", &num[i].u.d);
                break;
            default :
                printf("Error!!\n");
                return 0;
        }
    }

    power(num);

    printf("----------Result----------\n");
    for(int i = 0; i < n; i++) {
        switch(num[i].type) {
            case 1 :
                printf("%-10s: %d\n", num[i].name, num[i].u.i);
                break;
            case 2 :
                printf("%-10s: %.4f\n", num[i].name, num[i].u.f);
                break;
            case 3 :
                printf("%-10s: %.4lf\n", num[i].name, num[i].u.d);
                break;
            default :
                printf("Error!!\n");
                return 0;
        }
    }

    return 0;
}

void power(stemp *s)
{
    for(int i = 0; ; i++) {
        if(strcmp(s[i].name, "integer") == 0)
            s[i].u.i *= s[i].u.i;
        else if(strcmp(s[i].name, "float") == 0)
            s[i].u.f *= s[i].u.f;
        else if(strcmp(s[i].name, "double") == 0)
            s[i].u.d *= s[i].u.d;
        else 
            break;
    }
}