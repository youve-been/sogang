#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strCmpPr(char *s1, char *s2);
void strPk(char *s1, char *s2);

int main(void)
{
    char *s1, *s2;
    int k;

    s1 = (char *)malloc(101*sizeof(char));
    s2 = (char *)malloc(101*sizeof(char));

    printf("first string : ");
    fgets(s1, 100, stdin);
    printf("second string : ");
    fgets(s2, 100, stdin);

    strPk(s1, s2);
    k = strCmpPr(s1, s2);

    if(k == 0)
        printf("string1 = string2\n");
    else if(k == 1)
        printf("string1 > string2\n");
    else
        printf("string1 < string2\n");
    
    return 0;
}

int strCmpPr(char *s1, char *s2)
{
    int key;

    key = strcmp(s1, s2);

    if(key == 0)
        return 0;
    else if(key > 0)
        return 1;
    else
        return -1;
}

void strPk(char *s1, char *s2)
{
    int size1, size2, size_tmp;
    int index;
    char *tmp;

    tmp = (char *)malloc(101*sizeof(char));
    size1 = strlen(s1)-1;
    *(s1+size1) = '\0';
    size2 = strlen(s2)-1;
    *(s2+size2) = '\0';

    for(int i = 0; i < size1; i++) {
        if(((*(s1+i)>=65)&&(*(s1+i)<=90))||((*(s1+i)>=97)&&(*(s1+i)<=122))) {
            *(tmp + index) = *(s1 + i);
            index++;
        }
    }
    size_tmp = strlen(tmp);
    strcpy(s1, tmp);
    *(s1+size_tmp) = '\0';

    for(int i = 0; i < size_tmp; i++)
        *(tmp+i) = '\0';
    size_tmp = 0;
    index = 0;

    for(int i = 0; i < size2; i++) {
        if(((*(s2+i)>=65)&&(*(s2+i)<=90))||((*(s2+i)>=97)&&(*(s2+i)<=122))) {
            *(tmp + index) = *(s2 + i);
            index++;
        }
    }
    size_tmp = strlen(tmp);
    strcpy(s2, tmp);
    *(s2+size_tmp) = '\0';
}