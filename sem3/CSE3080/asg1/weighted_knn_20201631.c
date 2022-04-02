#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define K 5

int knn(float test[], int class[]);
void swap_f(float *a, float *b);
void swap_i(int *a, int *b);

float **data;
int n_data, n_feat, n_test;

int main(void)
{
    FILE *fp1, *fp2, *fp3;
    float **test;
    int i, j, *class;

    fp1 = fopen("data.txt", "rt");
    fp2 = fopen("test.txt", "rt");
    fp3 = fopen("output.txt", "wt");

    fscanf(fp1, "%d %d", &n_data, &n_feat);

    data = (float **)malloc(sizeof(float *)*n_data);
    for(i = 0; i < n_data; i++)
        data[i] = (float *)malloc(sizeof(float)*n_feat);
    class = (int *)malloc(sizeof(int)*n_data);
    
    for(i = 0; i < n_data; i++) {
        for(j = 0; j < n_feat; j++)
            fscanf(fp1, "%f", &data[i][j]);
        fscanf(fp1, "%d", &class[i]);
    }

    fscanf(fp2, "%d", &n_test);
    
    test = (float **)malloc(sizeof(float *)*n_test);
    for(i = 0; i < n_test; i++)
        test[i] = (float *)malloc(sizeof(float)*n_feat);

    for(i = 0; i < n_test; i++) {
        for(j = 0; j < n_feat; j++)
            fscanf(fp2, "%f", &test[i][j]);
    }

    for(i = 0; i < n_test; i++)
        fprintf(fp3, "%d\n", knn(test[i], class));

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}

int knn(float test[], int class[])
{
    int i, j, cnt, index = 0;
    int tmp_class[n_data], max_class[K], weight_class[K], flag[K] = {};
    float max_data[K], weight_data[K] = {};
    float *data_w, max;

    for(i = 0; i < n_data; i++)
        tmp_class[i] = class[i];

    data_w = (float *)malloc(sizeof(float)*n_data);

    for(i = 0; i < n_data; i++) {
        data_w[i] = 0;
        for(j = 0; j < n_feat; j++)
            data_w[i] += pow(test[j]-data[i][j], 2);
        data_w[i] = 1/sqrt(data_w[i]);
    }

    for(i = 0; i < K; i++) {
        max = data_w[i];
        for(j = i+1; j < n_data; j++) {
            if(max < data_w[j]) {
                max = data_w[j];
                swap_f(&data_w[i], &data_w[j]);
                swap_i(&tmp_class[j], &tmp_class[i]);
            }
        }
        max_class[i] = tmp_class[i];
        max_data[i] = max;
    }

    for(i = 0; i < K; i++) {
        for(j = 0; j < K; j++) {
            if(flag[i] == 0) {
                if(max_class[i] == max_class[j]) {
                    weight_class[i] = max_class[i];
                    weight_data[i] += max_data[j];
                    flag[j]++;
                }
            }
        }
    }

    for(i = 0, index = 0; i < K; i++) {
        if(weight_data[i] > weight_data[index])
            index = i;
    }


    return weight_class[index];
}

void swap_f(float *a, float *b)
{
    float tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap_i(int *a, int *b)
{
    int tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
}