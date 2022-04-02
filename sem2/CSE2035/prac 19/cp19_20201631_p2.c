#include <stdio.h>
#include <stdlib.h>

typedef struct node *nptr;

typedef struct {
    int count;
    nptr link;
} STACK;

typedef struct node {
    char data;
    nptr link;
} STACK_NODE;

void Push(STACK *pS, char mj);
int Pop(STACK *pS, char mj);

int main(void)
{
    int check = 1;
    char arr[101];

    STACK *pS;
    pS = (STACK *)malloc(sizeof(STACK));
    pS->link = NULL;
    pS->count = 0;

    scanf("%s", arr);

    for(int i = 0; arr[i] != '\0'; i++) {
        if((arr[i] == 40)||(arr[i] == 91)||(arr[i] == 123))
            Push(pS, arr[i]);
        else if((arr[i] == 41)||(arr[i] == 93)||(arr[i] == 125))
            check = Pop(pS, arr[i]);

        if(!check) {
            printf("Unmatched Parentheses!\n");
            return 0;
        }
    }
    
    if(pS->count)
        printf("Unmatched Parentheses!\n");
    else
        printf("Matched Parentheses!\n");

    return 0;
}

void Push(STACK *pS, char mj)
{
    STACK_NODE *pNew;

    pNew = (STACK_NODE *)malloc(sizeof(STACK_NODE));

    pNew->data = mj;
    pNew->link = pS->link;
    pS->link = pNew;

    pS->count++;
}

int Pop(STACK *pS, char mj)
{
    nptr pDel;

    if(pS->link) {
        pDel = pS->link;
        pS->link = pDel->link;
        free(pDel);
        pS->count--;
        return 1;
    }
    else
        return 0;
}