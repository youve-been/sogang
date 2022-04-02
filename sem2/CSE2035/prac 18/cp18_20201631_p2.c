#include <stdio.h>
#include <stdlib.h>

typedef struct node *nptr;

typedef struct node {
    char data;
    nptr link;
} NODE;

nptr head = NULL;

void InsertNodeAtFront(char a);
void InsertNodeAtBack(char b);
void PrintList();

int main(void) {
    InsertNodeAtFront('p');
    InsertNodeAtFront('p');
    InsertNodeAtFront('a');
    InsertNodeAtBack('l');
    InsertNodeAtBack('e');
    
    PrintList();

    return 0;
}

void InsertNodeAtFront(char a)
{
    NODE *pNew;
    pNew = (NODE *)malloc(sizeof(NODE));
    pNew->data = a;
    if(head == NULL)
        pNew->link = NULL;
    else
        pNew->link = head;

    head = pNew;
}

void InsertNodeAtBack(char b)
{
    NODE *pNew, *pPrev;
    pNew = (NODE *)malloc(sizeof(NODE));
    pNew->data = b;

    if(head == NULL)
        head = pNew;
    else {
        pPrev = head;
        while(pPrev->link != NULL)
            pPrev = pPrev->link;
        pPrev->link = pNew;
    }
    
    pNew->link = NULL;
}

void PrintList()
{
    NODE *pPrint;
    pPrint = head;
    while(pPrint != NULL) {
        printf("%c", pPrint->data);
        pPrint = pPrint->link;
    }
    printf("\n");
}