#include <stdio.h>
#include <stdlib.h>

enum Date getDate(int y, int m, int d);
char * getDay(enum Date currDate);

enum Date {sun=0, mon, tue, wed, thr, fri, sat};

struct Calender{
    int year, month, day;
    enum Date date;
    char *dataString;
};

int main(void)
{
    struct Calender Cal;

    Cal.dataString = (char *)malloc(10*sizeof(char));

    scanf("%d", &Cal.year);
    scanf("%d", &Cal.month);
    scanf("%d", &Cal.day);

    Cal.date = getDate(Cal.year, Cal.month, Cal.day);
    Cal.dataString = getDay(Cal.date);

    printf("%s\n", Cal.dataString);

    return 0;
}

enum Date getDate(int y, int m, int d)
{
    enum Date DATE;
    int k;

    k = (y + y/4 - y/100 + y/400 + (13*m+8)/5 + d) % 7;

    switch (k) {
        case 0 :
            DATE = sun;
            break;
        case 1 :
            DATE = mon;
            break;
        case 2 :
            DATE = tue;
            break;
        case 3 :
            DATE = wed;
            break;
        case 4 :
            DATE = thr;
            break;
        case 5 :
            DATE = fri;
            break;
        case 6 :
            DATE = sat;
            break;
    }

    return DATE;
}

char * getDay(enum Date currDate)
{
    char *str;
    str = (char *)malloc(10*sizeof(char));

    switch (currDate) {
        case 0 :
            str = "Sunday";
            break;
        case 1 :
            str = "Monday";
            break;
        case 2 :
            str = "Tuesday";
            break;
        case 3 :
            str = "Wednesday";
            break;
        case 4 :
            str = "Thursday";
            break;
        case 5 :
            str = "Friday";;
            break;
        case 6 :
            str = "Saturday";
            break;
    }

    return str;
}