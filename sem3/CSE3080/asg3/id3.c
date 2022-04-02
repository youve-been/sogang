#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _node *nptr;

typedef struct _node {
    int *data;
    nptr left, right;   //left : 0, right : 1
} NODE;

void Train(FILE *fp);
void sort(int feat, int **arr, int n_arr);
double EntRoot(int feat, int **arr, int n_arr);
double Ent(int feat, int col, int key, int **arr, int n_arr);
void swap(int a, int b, int **arr);
int Min(double *arr, int n_arr);

int **train, **test;

int main(void)
{
    FILE *fpTrain, *fpTest, *fpRes;

    fpTrain = fopen("train.txt", "rt");
    fpTest = fopen("test.txt", "rt");
    fpRes = fopen("results.txt", "wt");
    
    Train(fpTrain);

    return 0;
}

void Train(FILE *fp)
{
    int nCase, nFeat, cFeat, col;
    int i, j;
    nptr root;
    double ent_root, *ent_feat, *ent_nFeat;

    fscanf(fp, "%d %d %d", &nCase, &nFeat, &cFeat);
    col = nFeat + cFeat + 1;

    train = (int **)malloc(sizeof(int *)*nCase);
    for(i = 0; i < nCase; i++)
        train[i] = (int *)malloc(sizeof(int)*col);
    ent_feat = (double *)malloc(sizeof(double)*(col-1));
    ent_nFeat = (double *)malloc(sizeof(double)*(nCase-1));
    
    for(i = 0; i < nCase; i++) {
        for(j = 0; j < col; j++)
            fscanf(fp, "%d", &train[i][j]);
    }

    root = (NODE *)malloc(sizeof(NODE));

    ent_root = EntRoot(col-1, train, nCase);

    //nFeat의 entropy
    for(i = 0; i < nFeat; i++) {
        sort(i, train, nCase);
        for(j = 0; j < nCase - 1; j++)
            ent_nFeat[j] = Ent(i, col, train[j][i], train, nCase);
        ent_feat[i] = ent_nFeat[Min(ent_nFeat, nCase-1)];
    }

    //cFeat의 entropy
    for(i = nFeat; i < col-1; i++)
        ent_feat[i] = Ent(i, col, 0, train, nCase);

    //print
    for(i = 0; i < col-4; i++)
        printf("%d %lf\n", i, ent_feat[i]);
}

void sort(int feat, int **arr, int n_arr)
{
    int i, j;

    for(j = 0; j < n_arr-1; j++) {
        for(i = 0; i < n_arr-1; i++) {
            if(arr[i][feat] > arr[i+1][feat])
                swap(i, i+1, arr);
        }
    }
}

double EntRoot(int feat, int **arr, int n_arr)
{
    int i, cnt = 0;
    double ent, p;

    for(i = 0; i < n_arr; i++) {
        if(arr[i][feat] == 0)
            cnt++;
    }

    p = (double)cnt/n_arr;
    ent = -(p*log2(p) + (1-p)*log2(1-p));

    return ent;
}

double Ent(int feat, int col, int key, int **arr, int n_arr)
{
    int i;
    int cntL = 0;
    int cntM = 0;
    int totL = 0;
    double ent, entL, entM, pL, pM;

    for(i = 0; i < n_arr; i++) {
        if(arr[i][feat] <= key) {
            if(arr[i][col-1] == 0)
                cntL++;
            totL++;
        }
        else {
            if(arr[i][col-1] == 0)
                cntM++;
        }
    }
    //printf("%d, %d, %d\n", cntL, cntM, totL);

    pL = (double)cntL/totL;
    pM = (double)cntM/(n_arr-totL);
    if((pL == 0)||(pL == 1))
        entL = 0;
    else
        entL = -(pL*log2(pL) + (1-pL)*log2(1-pL));
    if((pM == 0)||(pM == 1))
        entM = 0;
    else
        entM = -(pM*log2(pM) + (1-pM)*log2(1-pM));

    ent = (totL*entL + (n_arr - totL)*entM)/n_arr;

    return ent;
}

void swap(int a, int b, int **arr)
{
    int *temp;

    temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

int Min(double *arr, int n_arr)
{
    int i, index = 0;
    double min = arr[0];

    for(i = 0; i < n_arr; i++) {
        if(min>arr[i]) {
            min = arr[i];
            index = i;
        }
    }

    return i;
}