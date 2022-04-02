#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int hours;
    int minutes;
    int seconds;
} Time;

void check_timer(Time *a);
Time *find_diff(Time *a, Time *b);

int main(void)
{
    char command[10];
    int checkpoint = 0;
    Time last, now, diff;
    Time *pl = &last;
    Time *pn = &now;
    Time *pd = &diff;

    check_timer(pl);

    printf("system > ");
    scanf("%s", command);

    while(strcmp(command, "quit") != 0) {
        if(strcmp(command, "check") != 0) {
            printf("WRONG COMMAND!!\n");
            printf("system > ");
            scanf("%s", command);
            continue;
        }
        check_timer(pn);
        checkpoint++;
        pd = find_diff(pn, pl);
        printf("\tCheck Point #%02d\n", checkpoint);
        printf("\tCurrent Time = %02d : %02d : %02d\n", pn->hours, pn->minutes, pn->seconds);
        printf("\tPrevious Time = %02d : %02d : %02d\n", pl->hours, pl->minutes, pl->seconds);
        printf("\tElapsed Time = %02d : %02d : %02d\n", pd->hours, pd->minutes, pd->seconds);
        *pl = *pn;
        printf("system > ");
        scanf("%s", command);
    }

    return 0;
}

void check_timer(Time *a)
{
    time_t timer;
    struct tm *t;

    timer = time(NULL);
    t = localtime(&timer);

    a->hours = t->tm_hour;
    a->minutes = t->tm_min;
    a->seconds = t->tm_sec;
}

Time *find_diff(Time *a, Time *b)
{
    Time diff;
    Time *pd = &diff;
    int carry = 0;

    if(b->seconds > a->seconds) {
        carry = -1;
        pd->seconds = a->seconds+60-b->seconds;
    }
    else {
        pd->seconds = a->seconds - b->seconds;
    }

    if(b->minutes > a->minutes+carry) {
        pd->minutes = a->minutes+60+carry-b->minutes;
    }
    else {
        pd->minutes = a->minutes + carry - b->minutes;
        carry = 0;
    }

    pd->hours = a->hours + carry - b->hours;

    return pd;
}