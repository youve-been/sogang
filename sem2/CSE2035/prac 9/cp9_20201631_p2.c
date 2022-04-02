#include <stdio.h>
#include <stdlib.h>

int check(char a);

int main(void)
{
    char *str;
    char *strAns;
    int size, index = 0;
    int index_tmp = 0;
    int count = 0;
    char *tmp;

    str = (char *)malloc(1001*sizeof(char));
    scanf("%s", str);

    for(int i = 0 ; ; i++) {
        if(*(str+i) == '\0') {
            size = i;
            break;
        }
    }

    strAns = (char *)malloc(1001*sizeof(char));
    tmp = (char *)malloc(size*sizeof(char));

    for(int i = 0 ; i < size; i++) {
        if(check(*(str+i)) == 0) {
            *(tmp + index_tmp) = *(str + i);
            index_tmp++;
        }
        else
        {
            for(int j = 0; check(*(str+i)) == 1; j++, i++) {
                count += *(str+i) - 48;
                count *= 10;
            }
            count /= 10;
            i--;
            for(int j = 0; j < count; j++) {
                for(int k = 0 ; ; k++, index++) {
                    if(*(tmp+k) == '\0')
                        break;
                    else
                        *(strAns+index) = *(tmp + k);
                    
                }
            }
            *tmp = '\0';
            index_tmp = 0;
            count = 0;
        }
    }

    for(int i = 0 ; ; i++) {
        if(*(strAns+i) == '\0') {
            size = i;
            break;
        }
    }

    for(int i = 0; i < size; i++)
        printf("%c", *(strAns+i));
    printf("\n");

    free(str);
    free(strAns);
    free(tmp);
    return 0;
}

int check(char a)
{
    if(a>=48 && a<= 57)
        return 1;
    else
        return 0;
}