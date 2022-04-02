#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _NODE {
    float *data;
    struct _NODE *link;
} NODE;

int num, feat, k, flag; //num = 데이터 개수, feat = 데이터 feature 개수, k = k값, flag = cluster의 변화 유무
void Insert(NODE *head, float *data);   //head 리스트의 마지막에 data를 저장한 노드 삽입
double Dist(NODE *n1, NODE *n2);   //두 노드 사이의 거리를 재는 함수
void Init(NODE **head);   //첫 cluster를 만드는 함수
int Min(double *arr, int index);   //주어진 배열에서 최솟값이 있는 인덱스를 반환하는 함수
void Print(NODE **head, FILE *fp);   //모든 리스트를 출력하는 함수
double Cluster(NODE **head);   //반복해서 clustering을 하고 medoid와의 거리 총 합을 반환하는 함수
void Change_Med(NODE **head);   //거리가 최소인 medoid를 구하는 함수.

int main()
{
    FILE *fpin, *fpout;
    NODE **head;
    int i, j, x, *c;
    float *arr;

    fpin = fopen("input.txt", "rt");
    fpout = fopen("output.txt", "wt");
    srand(1000);
    fscanf(fpin, "%d %d %d", &num, &feat, &k);
    head = (NODE **)malloc(sizeof(NODE *)*k);
    c = (int *)malloc(sizeof(int)*k);
    for(i = 0; i < k; i++) {
        head[i] = (NODE *)malloc(sizeof(NODE));
        head[i]->data = (float *)malloc(sizeof(float)*feat);
        head[i]->link == NULL;
        c[i] = rand()%num;
    }
    arr = (float *)malloc(sizeof(float)*feat);
    for(i = 0; i < num; i++) {
        for(j = 0; j < feat; j++)
            fscanf(fpin, "%f", &arr[j]);
        for(j = 0; j < k; j++) {
            if(i == c[j]) {
                for(x = 0; x < feat; x++)
                    head[j]->data[x] = arr[x];
                break;
            }
        }
        if(j == k)
            Insert(head[0], arr);
    }

    Init(head);
    do {
        Change_Med(head);
    } while(flag == 0);
    Print(head, fpout);

    return 0;
}

void Insert(NODE *head, float *data)
{
    NODE *p, *new;
    int i;
    new = (NODE *)malloc(sizeof(NODE));
    new->data = (float *)malloc(sizeof(float)*feat);
    p = head;
    for(i = 0; i < feat; i++)
        new->data[i] = data[i];
    while(p->link != NULL)
        p = p->link;
    p->link = new;
    p->link->link = NULL;
}

double Dist(NODE *n1, NODE *n2)
{
    int i;
    double dist = 0;

    for(i = 0; i < feat; i++)
        dist += pow((n1->data[i]-n2->data[i]), 2);
    dist = sqrt(dist);

    return dist;
}

void Init(NODE **head)
{
    int i;
    double *dist;
    NODE *p;
    p = head[0];
    dist = (double *)malloc(sizeof(double)*k);
    while(p->link != NULL) {
        for(i = 0; i < k; i++)
            dist[i] = Dist(p->link, head[i]);
        if(Min(dist, k) != 0) {
            Insert(head[Min(dist, k)], p->link->data);
            p->link = p->link->link;
        }
        p = p->link;
    }
}

int Min(double *arr, int index)
{
    int i, min = 0;
    for(i = 0; i < index; i++) {
        if(arr[min]>arr[i])
            min = i;
    }

    return min;
}

void Print(NODE **head, FILE *fp)
{
    int i, j;
    NODE *p;
    for(i = 0; i < k; i++) {
        fprintf(fp, "%d\n", i);
        p = head[i];
        while(p != NULL) {
            for(j = 0; j < feat; j++)
                fprintf(fp, "%f ", p->data[j]);
            fprintf(fp, "\n");
            p = p->link;
        }
    }
}

double Cluster(NODE **head)
{
    int i, j;
    double *dist, tot = 0;
    NODE *p, *temp;
    dist = (double *)malloc(sizeof(double)*k);
    flag = 0;
    for(i = 0; i < k; i++) {
        p = head[i];
        while(p->link != NULL) {
            for(j = 0; j < k; j++)
                dist[j] = Dist(p->link, head[j]);
            if(Min(dist, k) != i) {
                Insert(head[Min(dist, k)], p->link->data);
                temp = p->link;
                p->link = p->link->link;
                free(temp);
                flag = 1;
                if(p->link == NULL)
                    break;
            }
            tot += dist[Min(dist, k)];
            p = p->link;
        }
    }
    return tot;
}

void Change_Med(NODE **head)
{
    NODE *p, *temp;
    float *arr;
    int i, j, count = 0;
    double tmp, min = Cluster(head);
    arr = (float *)malloc(sizeof(float)*feat);
    for(i = 0; i < k; i++) {
        while(1) {
            p = head[i]->link;
            temp = head[i];
            head[i] = p;
            p = temp;
            tmp = Cluster(head);
            if(tmp <= min) {
                min = tmp;
                break;
            }
            else {
                temp = head[i];
                head[i] = p;
                p = temp;
                count++;
            }
            Insert(head[i], p->data);
            head[i]->link = head[i]->link->link;
            if(count == num/2)
                break;
        }
    }
}