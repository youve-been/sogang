#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *link;
} NODE;

typedef NODE *nptr;

void Insert(nptr *head, int data);
void Sort(nptr *head);
void PrintAll(nptr *head);
void swap(int *a, int *b);

int main(void)
{
    int A[10] = {3,9,8,2,5,10,7,1,4,6};
    nptr head = NULL;

    for(int i = 0; i < 10; i++)
        Insert(&head, A[i]);

    PrintAll(&head);

    Sort(&head);

    PrintAll(&head);

    return 0;
}

void Insert(nptr *head, int data)
{
    NODE *pNew, *pPrev;
    pNew = (NODE *)malloc(sizeof(NODE));
    pNew->data = data;

    if(*head == NULL)
        *head = pNew;
    else {
        pPrev = *head;
        while(pPrev->link != NULL)
            pPrev = pPrev->link;
        pPrev->link = pNew;
    }

    pNew->link = NULL;
}

void Sort(nptr *head)
{
    NODE *p;

    for(int i = 0; i < 9; i++) {
        p = *head;
        for(int j = 0; j < 9; j++) {
            if(p->data > p->link->data)
                swap(&p->data, &p->link->data);
            p = p->link;
        }
    }
}

void PrintAll(nptr *head)
{
    NODE *p;
    p = *head;
    while(p != NULL) {
        printf("%d ", p->data);
        p = p->link;
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}