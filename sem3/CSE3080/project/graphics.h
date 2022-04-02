/*그래픽 처리를 위한 구조체 및 데이터를 선언하는 헤더*/
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#define COLOR_BLACK 0
#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_YELLOW 3
#define COLOR_BLUE 4
#define COLOR_MAGENTA 5
#define COLOR_CYAN 6
#define COLOR_WHITE 7

typedef struct graphicFactor {
    char shape;
    int color;
} graphic;

#define BLANK {' ', COLOR_WHITE}

const int distance_table_x[6] = {1, 2, 3, 3, 4, 5};
const int distance_table_y[6] = {1, 1, 1, 2, 2, 3};

#endif