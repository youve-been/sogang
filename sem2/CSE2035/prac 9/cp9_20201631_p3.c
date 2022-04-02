#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *str_n, *str_m, *str_cm;
    int n, m, max = 0;
    int index_i, index_j;
    char **table;
    int i, j;

    scanf("%d", &n);
    scanf("%d", &m);

    str_n = (char *)malloc((n+1)*sizeof(char));
    str_m = (char *)malloc((m+1)*sizeof(char));

    scanf("%s", str_n);
    scanf("%s", str_m);

    table = (char **)malloc((n+1)*sizeof(char *));
    for(i = 0; i < n+1; i++)
        *(table+i) = (char *)malloc((m+1)*sizeof(char));
    
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            if(*(str_n+i) == *(str_m+j)) {
                if(i == 0 || j == 0)
                    *(*(table+i)+j) = 1;
                else
                    *(*(table+i)+j) = *(*(table+i-1)+j-1) + 1;
            }
            else
                *(*(table+i)+j) = 0;
        }
    }

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            if(max < *(*(table+i)+j)) {
                max = *(*(table+i)+j);
                index_i = i;
                index_j = j;
            }
        }
    }

    str_cm = (char *)malloc((max+1)*sizeof(char));

    for(i = index_i-max+1, j = 0; i <= index_i; i++, j++) {
        *(str_cm + j) = *(str_n+i);
    }

    printf("Longest Common Substring = %s\n", str_cm);

    return 0;
}