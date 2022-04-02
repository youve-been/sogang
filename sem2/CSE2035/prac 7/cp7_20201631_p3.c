#include <stdio.h>
#include <stdlib.h>

int *merge(int *ary1, int size1, int *ary2, int size2, int *ary3, int size3);
void sort(int *a, int size);
void swap(int *a, int *b);

int main(void)
{
    int *a;
    int *ary1;
    int *ary2;
    int *ary3;

    a = (int *)calloc(12, sizeof(int));
    ary1 = (int *)calloc(3, sizeof(int));
    ary2 = (int *)calloc(4, sizeof(int));
    ary3 = (int *)calloc(5, sizeof(int));

    printf("Input 12 integer : ");

    for(int i = 0; i < 12; i++)
        scanf("%d", a+i);
    
    printf("Array 1\t\t : ");
    for(int i = 0; i < 3; i++) {
        *(ary1+i) = *(a+i);
        printf("%d ", *(a+i));
    }
    sort(ary1, 3);
    printf("\n");

    printf("Array 2\t\t : ");
    for(int i = 0; i < 4; i++) {
        *(ary2+i) = *(a+i+3);
        printf("%d ", *(a+i+3));
    }
    sort(ary2, 4);
    printf("\n");
    
    printf("Array 3\t\t : ");
    for(int i = 0; i < 5; i++) {
        *(ary3+i) = *(a+i+7);
        printf("%d ", *(a+i+7));
    }
    sort(ary3, 5);
    printf("\n");
    
    a = merge(ary1, 3, ary2, 4, ary3, 5);

    printf("result Array : ");

    for(int i = 0; i < 12; i++)
        printf("%d ", *(a+i));
    printf("\n");

    return 0;
}

int *merge(int *ary1, int size1, int *ary2, int size2, int *ary3, int size3)
{
    int *a;
    int min1 = 0;
    int min2 = 0;
    int min3 = 0;

    a = (int *)calloc(12, sizeof(int));

    for(int i = 0; i < 12; i++) {
        if(min1>=3) {
            if(min2>=4) {
                *(a+i) = *(ary3+min3);
                min3++;
            }
            else if(min3>=5) {
                *(a+i) = *(ary2+min2);
                min2++;
            }
            else {
                if(*(ary2+min2)<=*(ary3+min3)) {
                    *(a+i) = *(ary2+min2);
                    min2++;
                }
                else {
                    *(a+i) = *(ary3+min3);
                    min3++;
                }
            }
        }
        else if(min2>=4){
            if(min1>=1) {
                *(a+i) = *(ary3+min3);
                min3++;
            }
            else if(min3>=5) {
                *(a+i) = *(ary1+min1);
                min1++;
            }
            else {
                if(*(ary1+min1)<=*(ary3+min3)) {
                    *(a+i) = *(ary1+min1);
                    min1++;
                }
                else {
                   *(a+i) = *(ary3+min3);
                   min3++;
                }
            }
        }
        else if(min3>=5) {
            if(min2>=4) {
                *(a+i) = *(ary3+min3);
                min3++;
            }
            else if(min1>=3) {
                *(a+i) = *(ary1+min1);
                min1++;
            }
            else {
                if(*(ary2+min2)<=*(ary1+min1)) {
                    *(a+i) = *(ary2+min2);
                    min2++;
                }
                else {
                    *(a+i) = *(ary1+min1);
                    min1++;
                }
            }
        }
        else {
            if((*(ary1+min1)<=*(ary2+min2))&&(*(ary1+min1)<=*(ary3+min3))) {
                *(a+i) = *(ary1+min1);
                min1++;
            }
            else if((*(ary2+min2)<=*(ary1+min1))&&(*(ary2+min2)<=*(ary3+min3))) {
                *(a+i) = *(ary2+min2);
                min2++;
            }
            else if((*(ary3+min3)<=*(ary1+min1))&&(*(ary3+min3)<=*(ary2+min2))) {
                *(a+i) = *(ary3+min3);
                min3++;
            }
        }
    }

    return a;
}

void sort(int *a, int size)
{
    int min;

    for(int i = 0; i < size; i++) {
        min = i;

        for(int j = i+1; j < size; j++) {
            if(*(a+j) < *(a+min))
                min = j;
        }

        if(i != min)
            swap(a+i, a+min);
    }
}

void swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}