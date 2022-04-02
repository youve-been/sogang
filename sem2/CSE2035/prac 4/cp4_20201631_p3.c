#include <stdio.h>

void count(int board[][100], int n, int m);

int main(void)
{
    int n, m;
    int board[100][100];
    
    scanf("%d %d", &n, &m);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            scanf("%d", (*(board+i)+j));
    }
    count(board, n, m);
    
    return 0;
}

void count(int board[][100], int n, int m)
{
    int ans = 0;
    int check[100][100] = {0};
    int temp = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(*(*(board+i)+j) == 0) {
                if(temp >= 2) {
                    temp = 0;
                    continue;
                }
                if(*(*(check+i)+j) == 1)
                    continue;
                if((j == m-1)||(*(*(check+i)+j+1) == 1)) {
                    *(*(board+i)+j) += 1;
                    j--;
                    temp++;
                    continue;
                }
                *(*(check+i)+j) = 1;
                *(*(check+i)+j+1) = 1;
                ans++;
            }
            else if(*(*(board+i)+j) == 1) {
                if(*(*(check+i)+j) == 1)
                    continue;
                if((i == n-1)||(*(*(check+i+1)+j) == 1)) {
                    *(*(board+i)+j) -= 1;
                    j--;
                    temp++;
                    continue;
                }
                *(*(check+i)+j) = 1;
                *(*(check+i+1)+j) = 1;
                ans++;
            }
            temp = 0;
        }
    }
    
    printf("%d\n", ans);
}
