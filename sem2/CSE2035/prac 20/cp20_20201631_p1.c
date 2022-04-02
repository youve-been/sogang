#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} QUEUE_NODE;

typedef struct {
    QUEUE_NODE *front;
    int count;
    QUEUE_NODE *rear;
} QUEUE;

void Exit(QUEUE *q);
void Enqueue(QUEUE *q);
void PrintAll(QUEUE q);
void Dequeue(QUEUE *q);

int main(void)
{
    int choice;
    QUEUE *q;

    q = (QUEUE *)malloc(sizeof(QUEUE));
    q->front = NULL;
    q->count = 0;
    q->rear = NULL;

    printf("****** Menu ******\n");
    printf("* 0 : Exit       *\n");
    printf("* 1 : Enqueue    *\n");
    printf("* 2 : Dequeue    *\n");
    printf("* 3 : Print All  *\n");
    printf("******************\n");
    do {
        printf("Select > ");
        scanf("%d", &choice);
        switch(choice) {
            case 0 :
                Exit(q);
                break;
            case 1 :
                Enqueue(q);
                break;
            case 2 :
                Dequeue(q);
                break;
            case 3 :
                PrintAll(*q);
                break;
            default :
                printf("Input Error! - Try Again!\n");
                break;
        }
    } while(choice);

    return 0;
}

void Exit(QUEUE *q)
{
    QUEUE_NODE *p;
    while(q->count != 0) {
        p = q->front;
        q->front = q->front->next;
        free(p);
        q->count--;
    }
    free(q);
}

void Enqueue(QUEUE *q)
{
    int num;

    QUEUE_NODE *p;
    p = (QUEUE_NODE *)malloc(sizeof(QUEUE_NODE));
    printf("Input Data > ");
    scanf("%d", &num);
    p->data = num;
    p->next = NULL;
    if(q->front == NULL)
        q->front = p;
    else
        q->rear->next = p;
    q->rear = p;
    q->count++;
}

void PrintAll(QUEUE q)
{
    QUEUE_NODE *p;
    p = q.front;
    while(p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\nQueue Level : %d\n", q.count);
}

void Dequeue(QUEUE *q)
{
    if(q->count == 0)
        printf("Empty!\n");
    else {
        QUEUE_NODE *p;
        p = q->front;
        printf("Dequeue %d\n", p->data);
        q->front = q->front->next;
        free(p);
        q->count--;
    }
}