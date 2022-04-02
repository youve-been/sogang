#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;

typedef struct node {
    int data;
    struct node *link;
} NODE;

void Insert(NODE **head, int js);
void Delete(NODE **head);
void PrintAll(NODE **head);

int main(void)
{
    int A[10] = {3, 9, 8, 2, 5, 10, 7, 1, 4, 6};

    NODE *head = NULL;

    for(int i = 0; i < 10; i++)
        Insert(&head, A[i]);
    
    PrintAll(&head);
    
    for(int i = 0; i < 10; i++) {
        Delete(&head);
        PrintAll(&head);
    }
    
    return 0;
}

void Insert(NODE **head, int js)
{
    NODE *pNew, *pPrev;
    pNew = (NODE *)malloc(sizeof(NODE));
    pNew->data = js;

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

void Delete(NODE **head)
{
    NODE *ptr;

    ptr = (*head)->link;
    free(*head);
    *head = ptr;
}

void PrintAll(NODE **head)
{
    NODE *p;
    p = *head;
    if(*head == NULL)
        printf("Empty");
    else {
        while(p != NULL) {
            printf("%d ", p->data);
            p = p->link;
        }
    }
    printf("\n");
}