#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double VectorSize;
typedef double Distance;
typedef double Scalar;

typedef struct {
    float comps;
    int vec_size;
} vector;

VectorSize vSize(vector *v);
Distance DistVector(vector *v1, vector *v2);
Scalar innerProduct(vector *v1, vector *v2);

int main (void)
{
    int n, m;
    vector *v1, *v2;

    scanf("%d", &n);
    v1 = (vector*)malloc(sizeof(vector)*n);
    v1[0].vec_size = n;
    for(int i = 0; i < v1[0].vec_size; i++)
        scanf("%f", &v1[i].comps);
    scanf("%d", &n);
    v2 = (vector*)malloc(sizeof(vector)*n);
    v2[0].vec_size = n;
    for(int i = 0; i < v2[0].vec_size; i++)
        scanf("%f", &v2[i].comps);

    if(v1[0].vec_size == v2[0].vec_size) {
        printf("%.2lf\n", vSize(v1));
        printf("%.2lf\n", vSize(v2));
        printf("%.2lf\n", DistVector(v1, v2));
        printf("%.2lf\n", innerProduct(v1, v2));
    }
    else {
        printf("%.2lf\n", vSize(v1));
        printf("%.2lf\n", vSize(v2));
    }

    return 0;
}

VectorSize vSize(vector *v)
{
    double size = 0;

    for(int i = 0; i < v[0].vec_size; i++)
        size += pow((double)v[i].comps, 2);
    
    size = sqrt(size);

    return size;
}

Distance DistVector(vector *v1, vector *v2)
{
    double dist = 0;

    for(int i = 0; i < v1[0].vec_size; i++)
        dist += pow((double)v1[i].comps - v2[i].comps, 2);

    dist = sqrt(dist);

    return dist;
}

Scalar innerProduct(vector *v1, vector *v2)
{
    double prod = 0;

    for(int i = 0; i < v1[0].vec_size; i++)
        prod += (double)v1[i].comps * v2[i].comps;

    return prod;
}