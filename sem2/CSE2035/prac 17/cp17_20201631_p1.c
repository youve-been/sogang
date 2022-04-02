#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
    double z;
    double r;
} SPHERE;

double Distance(SPHERE a, SPHERE b);
double CrossSectionArea(SPHERE a, SPHERE b);
double SurfaceArea(SPHERE a, SPHERE b);
double Volume(SPHERE a, SPHERE b);

int main(void)
{
    SPHERE a, b;
    double key, res;

    printf("Type First Sphere Coordinate : ");
    scanf("%lf %lf %lf", &a.x, &a.y, &a.z);
    printf("Type First Sphere Radius : ");
    scanf("%lf", &a.r);
    printf("Type Second Sphere Coordinate : ");
    scanf("%lf %lf %lf", &b.x, &b.y, &b.z);
    printf("Type Second Sphere Radius : ");
    scanf("%lf", &b.r);

    key = Distance(a,b);

    if(key>(a.r+b.r)) {
        res = CrossSectionArea(a,b);
        printf("Sum of Cross Section Area : %.2lf\n", res);
    }
    else if(key == (a.r+b.r)) {
        res = SurfaceArea(a,b);
        printf("Sum of Surface Area : %.2lf\n", res);
    }
    else {
        res = Volume(a,b);
        printf("Sum of Volume : %.2lf\n", res);
    }

    return 0;
}

double Distance (SPHERE a, SPHERE b)
{
    double key;

    key = sqrt((a.x - b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z));

    return key;
}

double CrossSectionArea(SPHERE a, SPHERE b)
{
    double res;

    res = 3.14*(a.r*a.r + b.r*b.r);

    return res;
}

double SurfaceArea(SPHERE a, SPHERE b)
{
    double res;

    res = 3.14*4*(a.r*a.r+b.r*b.r);
    
    return res;
}

double Volume(SPHERE a, SPHERE b)
{
    double res;

    res = 4*3.14*(a.r*a.r*a.r+b.r*b.r*b.r)/3;

    return res;
}