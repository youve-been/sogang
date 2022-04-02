#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char command[10];
    struct node *next;
} QUEUE_NODE;

typedef struct {
    QUEUE_NODE *front;
    int count;
    QUEUE_NODE *rear;
} QUEUE;

int CheckCommand(char *command);
void EnqueueCommand(QUEUE *pQueue, char *dataIn);
int DequeuePrint(QUEUE *pQueue, char *dataOut);

int main(void)
{
    char command[10];
    QUEUE *pQueue;
    pQueue = (QUEUE *)malloc(sizeof(QUEUE));

    pQueue->front = NULL;
    pQueue->count = 0;
    pQueue->rear = NULL;

    while(1) {
        printf(">>");
        scanf("%s", command);
        if(CheckCommand(command)) {
            if(!(strcmp(command, "history")&&strcmp(command, "h"))) {
                while(1) {
                    char comm[10];
                    if(DequeuePrint(pQueue, comm) == 0)
                        break;
                    printf("%s\n", comm);
                }
            }
            else if(!(strcmp(command, "quit")&&strcmp(command, "q"))) {
                QUEUE_NODE *p;
                while(pQueue->count != 0) {
                    p = pQueue->front;
                    pQueue->front = pQueue->front->next;
                    free(p);
                    pQueue->count--;
                }
                break;
            }
            else {
                EnqueueCommand(pQueue, command);
                printf("[Valid] %s\n", command);
            }
        }
        else {
            printf("[Invalid]\n");
        }
    }

    free(pQueue);

    return 0;
}

int CheckCommand(char *command)
{
    if(!(strcmp(command, "help")&&strcmp(command, "dir")&&strcmp(command,"mkdir")&&strcmp(command, "cd")&&strcmp(command, "history")&&strcmp(command, "h")&&strcmp(command, "quit")&&strcmp(command, "q")))
        return 1;
    else
        return 0;
}

void EnqueueCommand(QUEUE *pQueue, char *dataIn)
{
    QUEUE_NODE *p;

    p = (QUEUE_NODE *)malloc(sizeof(QUEUE_NODE));

    strcpy(p->command,dataIn);
    p->next = NULL;
    if(pQueue->front == NULL)
        pQueue->front = p;
    else
        pQueue->rear->next = p;
    pQueue->rear = p;
    pQueue->count++;
}

int DequeuePrint(QUEUE *pQueue, char *dataOut)
{

    if(pQueue->count == 0)
        return 0;
    else {
        QUEUE_NODE *p;
        p = pQueue->front;
        strcpy(dataOut, p->command);
        pQueue->front = pQueue->front->next;
        free(p);
        pQueue->count--;
        return 1;
    }
}