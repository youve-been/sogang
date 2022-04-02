#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char dept_name[25];
    int dept_no;
} dept;

enum Gender {Male = 0, Female};

typedef struct {
    int employee_id;
    char name[25];
    enum Gender gender;
    dept department;
    double salary;
} employee_data;

int search(employee_data *e, int num, int keyword);
employee_data update(employee_data e, int n);

int main(void)
{
    char cont = 'y';
    int key_id, change;
    int n, index;
    char gen[10];
    char name_1[20], name_2[20];
    employee_data *e;
    FILE *fp;

    fp = fopen("16_input.txt", "rt");

    fscanf(fp, "%d", &n);
    printf("%d\n", n);

    e = (employee_data *)malloc(sizeof(employee_data)*n);

    for(int i = 0; i < n; i++) {
        fscanf(fp, "%d / %s %s / %s / %s / %d / %lf", &e[i].employee_id, name_1, name_2, gen, e[i].department.dept_name, &e[i].department.dept_no, &e[i].salary);
        strcpy(e[i].name, name_1);
        strcat(e[i].name, " ");
        strcat(e[i].name, name_2);
        if(strcmp(gen, "Male") == 0)
            e[i].gender = Male;
        else if(strcmp(gen, "Female") == 0)
            e[i].gender = Female;
    }

    do {
        printf("Employee ID : ");
        scanf("%d", &key_id);

        index = search(e, n, key_id);
        if(index == 26) {
            printf("No employee\n");
            continue;
        }
        printf("------Employee Data------\n");
        printf("%d / %s / ", e[index].employee_id, e[index].name);
        if(e[index].gender == Male)
            printf("Male");
        else
            printf("Female");
        printf(" / %s / %d / %.2lf\n", e[index].department.dept_name, e[index].department.dept_no, e[index].salary);

        printf("------Updated Information------\n");
        printf("Input the department Number : ");
        scanf("%d", &change);

        e[index] = update(e[index], change);
        printf("------Updated employee data----\n");
        printf("%d / %s / ", e[index].employee_id, e[index].name);
        if(e[index].gender == Male)
            printf("Male");
        else
            printf("Female");
        printf(" / %s / %d / %.2lf\n", e[index].department.dept_name, e[index].department.dept_no, e[index].salary);

        printf("Continue? (y/n) : ");
        scanf("%*c%c", &cont);
    } while(cont != 'n');
    
    fclose(fp);

    return 0;
}

int search(employee_data *e, int num, int keyword)
{
    int i;

    for(i = 0; i < num; i++) {
        if(keyword == e[i].employee_id)
            break;
    }

    return i;
}

employee_data update(employee_data e, int n)
{
    employee_data new;

    new.employee_id = e.employee_id;
    new.gender = e.gender;
    new.salary = e.salary;
    strcpy(new.name, e.name);

    new.department.dept_no = n;
    switch(n) {
        case 1:
            strcpy(new.department.dept_name, "FINANCE");
            break;
        case 2:
            strcpy(new.department.dept_name, "SALES");
            break;
        case 3:
            strcpy(new.department.dept_name, "RESEARCH");
            break;
        case 4:
            strcpy(new.department.dept_name, "PLANNING");
            break;
    }

    return new;
}