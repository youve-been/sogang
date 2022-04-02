#include <stdio.h>

typedef struct {
    int numerator;
    int denominator;
} FRACTION;

void getFr(FRACTION *pFr);
void addFr(FRACTION *pFr1, FRACTION *pFr2, FRACTION *pRes);
void subFr(FRACTION *pFr1, FRACTION *pFr2, FRACTION *pRes);
void multFr(FRACTION *pFr1, FRACTION *pFr2, FRACTION *pRes);
void divFr(FRACTION *pFr1, FRACTION *pFr2, FRACTION *pRes);
void printFr(FRACTION *pFr1, FRACTION *pFr2, FRACTION *pRes, char op);
void findKY(FRACTION *pFr);

int main(void)
{
    FRACTION Fr1, Fr2, Res;
    FRACTION *pFr1 = &Fr1;
    FRACTION *pFr2 = &Fr2;
    FRACTION *pRes = &Res;
    
    getFr(pFr1);
    getFr(pFr2);
    printf("\n");
    findKY(pFr1);
    findKY(pFr2);

    addFr(pFr1, pFr2, pRes);
    printFr(pFr1, pFr2, pRes, '+');
    printf("\n");
    subFr(pFr1, pFr2, pRes);
    printFr(pFr1, pFr2, pRes, '-');
    printf("\n");
    multFr(pFr1, pFr2, pRes);
    printFr(pFr1, pFr2, pRes, '*');
    printf("\n");
    divFr(pFr1, pFr2, pRes);
    printFr(pFr1, pFr2, pRes, '/');

    return 0;
}

void getFr(FRACTION *pFr)
{
    printf("Write a fraction in the form of x/y : ");
    scanf("%d/%d", &pFr->numerator, &pFr->denominator);
}

void addFr(FRACTION *pFr1, FRACTION *pFr2, FRACTION *pRes)
{
    pRes->denominator = pFr1->denominator * pFr2->denominator;
    pRes->numerator = pFr1->numerator * pFr2->denominator + pFr1->denominator * pFr2->numerator;

    findKY(pRes);
}

void subFr(FRACTION *pFr1, FRACTION *pFr2, FRACTION *pRes)
{
    pRes->denominator = pFr1->denominator * pFr2->denominator;
    pRes->numerator = pFr1->numerator * pFr2->denominator - pFr1->denominator * pFr2->numerator;

    findKY(pRes);
}

void multFr(FRACTION *pFr1, FRACTION *pFr2, FRACTION *pRes)
{
    pRes->denominator = pFr1->denominator * pFr2->denominator;
    pRes->numerator = pFr1->numerator * pFr2->numerator;

    findKY(pRes);
}

void divFr(FRACTION *pFr1, FRACTION *pFr2, FRACTION *pRes)
{
    pRes->denominator = pFr1->denominator * pFr2->numerator;
    pRes->numerator = pFr1->numerator * pFr2->denominator;

    findKY(pRes);
}

void printFr(FRACTION *pFr1, FRACTION *pFr2, FRACTION *pRes, char op)
{
    printf("The result of %d/%d %c %d/%d is %d/%d\n", pFr1->numerator, pFr1->denominator, op, pFr2->numerator, pFr2->denominator, pRes->numerator, pRes->denominator);
}

void findKY(FRACTION *pFr)
{
    int p, q, tmp;

    p = pFr->numerator;
    q = pFr->denominator;

    while(q != 0) {
        tmp = p;
        p = q;
        q = tmp%q;
    }

    pFr->numerator /= p;
    pFr->denominator /= p; 
}