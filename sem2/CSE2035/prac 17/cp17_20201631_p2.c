#include <stdio.h>
#include <stdlib.h>

typedef struct _SUBJECT_{
    char number[8];
    int credit;
    double grade;
} subject;

typedef struct _STUDENT_{
    int id;
    int number_of_course;
    subject *courses;
} student;

double calcCGPA(student s);

int main(void)
{
    int n;
    student *s;
    double *CGPA;

    scanf("%d", &n);
    s = (student *)malloc(sizeof(student)*n);
    CGPA = (double *)malloc(sizeof(double)*n);
    
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &s[i].id, &s[i].number_of_course);
        s[i].courses = (subject *)malloc(sizeof(subject)*s[i].number_of_course);
        for(int j = 0; j < s[i].number_of_course; j++)
            scanf("%s %d %lf", s[i].courses[j].number, &s[i].courses[j].credit, &s[i].courses[j].grade);
        CGPA[i] = calcCGPA(s[i]);
    }
    printf("==========\n");

    for(int i = 0; i < n; i++) 
        printf("%d / %.6lf\n", s[i].id, CGPA[i]);

    return 0;
}

double calcCGPA(student s)
{
    double cgpa = 0;
    int credit_total = 0;

    for(int i = 0; i < s.number_of_course; i++) {
        cgpa += s.courses[i].credit * s.courses[i].grade;
        credit_total += s.courses[i].credit;
    }
    
    cgpa /= credit_total;

    return cgpa;
}