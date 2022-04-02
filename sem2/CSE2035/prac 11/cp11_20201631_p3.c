#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *dir, *name;
    int size, i, j, size_new;

    dir = (char *)malloc(1001*sizeof(char));
    name = (char *)malloc(1001*sizeof(char));

    printf("Path : ");
    fgets(dir, 1000, stdin);
    size = strlen(dir) - 1;
    *(dir+size) = '\0';

    printf("File name : ");
    fgets(name, 1000, stdin);
    size_new = strlen(name) - 1;
    *(name+size_new) = '\0';

    for(i = size; ; i--) {
        if(*(dir+i) == 47) {
            *(dir+i+1) = '\0';
            break;
        }
    }
    
    printf("New path : %s%s\n", dir, name);

    return 0;
}