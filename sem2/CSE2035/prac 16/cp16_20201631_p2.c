#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number;
    char id[50];
    char pw[50];
    char name[50];
    char address[200];
} customer;

int main(void)
{
    int i, n;
    int count = 0;
    char id_tmp[50], tmp[30];
    char pw_tmp[50];
    char ch;
    customer *cus;
    FILE *fp;

    fp = fopen("customer.txt", "r");

    cus = (customer *)malloc(sizeof(customer)*1000);

    fscanf(fp, "%[^\n]", tmp);
    for(i = 0; ; i++) {
        fscanf(fp, "%d %*c %[^,] %*c %[^,] %*c %[^,] %*c", &cus[i].number, cus[i].id, cus[i].pw, cus[i].name);
        fgets(cus[i].address, 200, fp);
        if(feof(fp) != 0)
            break;
        else
            cus[i].address[strlen(cus[i].address)-1] = '\0';
    }

    n = i + 1;

    printf("로그인 프로그램\n");

    do {
        printf("아이디 : ");
        scanf("%s", id_tmp);
        printf("패스워드 : ");
        scanf("%s", pw_tmp);

        for(i = 0; i < n; i++) {
            if((strcmp(id_tmp, cus[i].id) == 0)&&(strcmp(pw_tmp, cus[i].pw) == 0)) {
                printf("====================\n");
                printf("회원번호 : %d\n", cus[i].number);
                printf("아이디 : %s\n", cus[i].id);
                printf("패스워드 : %s\n", cus[i].pw);
                printf("이름 : %s\n", cus[i].name);
                printf("주소 : %s\n", cus[i].address);
                count = -1;
                break;
            }
        }
        if(count == -1)
            break;
        else
            printf("일치하는 회원이 없습니다.\n");
        
        count++;
    } while(count < 3);

    fclose(fp);

    return 0;
}