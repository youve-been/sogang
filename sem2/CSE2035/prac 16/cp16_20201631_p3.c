#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int num;
    char name[20];
    int level;
    char type1[30];
    char type2[30];

    char sk1[20];
    char sk2[20];
    char sk3[20];
    char sk4[20];
} dex;

typedef struct {
    int inx;
    char name[10];
    char region[10];
    dex poke[6];
} user;

int main(void)
{
    char name_tmp[10];
    int i, j, k, count = 0;
    user *master;
    FILE *fp;

    fp = fopen("user.txt", "r");

    master = (user *)malloc(sizeof(user)*100);

    for(i = 0; ; i++) {
        fscanf(fp, "%s", name_tmp);
        for(j = 0; j < count; j++) {
            if(strcmp(master[j].name, name_tmp) == 0) {
                master[j].inx++;
                break;
            }
        }
        if(j == count) {
            strcpy(master[j].name, name_tmp);
            master[j].inx = 1;
            count++;
        }
        
        fscanf(fp, "%s", master[j].region);
        fscanf(fp, "%d", &master[j].poke[master[j].inx-1].num);
        fscanf(fp, "%s", master[j].poke[master[j].inx-1].name);
        fscanf(fp, "%d", &master[j].poke[master[j].inx-1].level);
        fscanf(fp, "%s", master[j].poke[master[j].inx-1].type1);
        for(k = 0; k <= strlen(master[j].poke[master[j].inx-1].type1); k++) {
            if(master[j].poke[master[j].inx-1].type1[k] == ',') {
                break;
            }
        }
        if(k > strlen(master[j].poke[master[j].inx-1].type1))
            strcpy(master[j].poke[master[j].inx-1].type2, master[j].poke[master[j].inx-1].type1);
        else {
            strcpy(master[j].poke[master[j].inx-1].type2, master[j].poke[master[j].inx-1].type1+k+1);
            master[j].poke[master[j].inx-1].type1[k] = '\0';
        }
        fscanf(fp, "\t %[^,] %*c %[^,] %*c %[^,] %*c %s", master[j].poke[master[j].inx-1].sk1,master[j].poke[master[j].inx-1].sk2, master[j].poke[master[j].inx-1].sk3, master[j].poke[master[j].inx-1].sk4);
        if(feof(fp) != 0)
            break;
    }

    printf("Number of Users = %d\n\n", count);

    for(i = 0; i < count; i++) {
        printf("[Name] %s(%s)\n", master[i].name, master[i].region);
        printf(" [Pokemon]\n");
        for(j = 0; j < master[i].inx; j++) {
            printf("  [Name]%s(%d)\n", master[i].poke[j].name, master[i].poke[j].num);
            printf("  [Level]%d\n", master[i].poke[j].level);
            if(strcmp(master[i].poke[j].type1, master[i].poke[j].type2) == 0)
                printf("  [Type]%s\n", master[i].poke[j].type1);
            else {
                printf("  [Type1]%s\n", master[i].poke[j].type1);
                printf("  [Type2]%s\n", master[i].poke[j].type2);
            }
            printf("  [Skill1]%s\n", master[i].poke[j].sk1);
            printf("  [Skill2]%s\n", master[i].poke[j].sk2);
            printf("  [Skill3]%s\n", master[i].poke[j].sk3);
            printf("  [Skill4]%s\n\n", master[i].poke[j].sk4);
        }
    }

    fclose(fp);

    return 0;
    
}