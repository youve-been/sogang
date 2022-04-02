#include <stdio.h>

struct CoinBox{
    int n500;
    int n100;
    int n50;
    int n10;
};

int main(void)
{
    struct CoinBox coin;
    int change;

    scanf("%d", &change);

    coin.n500 = change/500;
    change %= 500;
    coin.n100 = change/100;
    change %= 100;
    coin.n50 = change/50;
    change %= 50;
    coin.n10 = change/10;

    printf("%d\n%d\n%d\n%d\n", coin.n500, coin.n100, coin.n50,coin.n10);

    return 0;
}