/*몹의 생김새를 저장하는 헤더*/
#ifndef _MOB_GRAPHIC_INFO_H_
#define _MOB_GRAPHIC_INFO_H_

#include "graphics.h"

#define MAX_SIZE 6
#define GRAPHIC_WIDTH 5
#define GRAPHIC_HEIGHT 3
#define STATE 2
#define LEFT 0
#define RIGHT 1

#define MOB_COLOR_1 COLOR_MAGENTA
#define MOB_COLOR_2 COLOR_RED

const graphic mob_graphic[MAX_SIZE][STATE][GRAPHIC_HEIGHT][GRAPHIC_WIDTH] = {
    {//[0][][][]
        {//[0][0][][]
            {BLANK, BLANK, BLANK, BLANK, BLANK},
            {BLANK, BLANK, {'@', MOB_COLOR_1}, BLANK, BLANK},
            {BLANK, BLANK, BLANK, BLANK, BLANK}
        },
        {//[0][1][][]
            {BLANK, BLANK, BLANK, BLANK, BLANK},
            {BLANK, BLANK, {'@', MOB_COLOR_1}, BLANK, BLANK},
            {BLANK, BLANK, BLANK, BLANK, BLANK}
        }
    },
    {//[1][][][]
        {//[1][0][][]
            {BLANK, BLANK, BLANK, BLANK, BLANK},
            {BLANK, BLANK, {'@', MOB_COLOR_2}, {'<', MOB_COLOR_1}, BLANK},
            {BLANK, BLANK, BLANK, BLANK, BLANK}
        },
        {//[1][1[][]
            {BLANK, BLANK, BLANK, BLANK, BLANK},
            {BLANK, {'>', MOB_COLOR_1}, {'@', MOB_COLOR_2}, BLANK, BLANK},
            {BLANK, BLANK, BLANK, BLANK, BLANK}
        }
    },
    {//[2][][][]
        {//[2][0][][]
            {BLANK, BLANK, BLANK, BLANK, BLANK},
            {BLANK, {'<', MOB_COLOR_1}, {'@', MOB_COLOR_2}, {'<', MOB_COLOR_1}, BLANK},
            {BLANK, BLANK, BLANK, BLANK, BLANK}
        },
        {//[2][1][][]
            {BLANK, BLANK, BLANK, BLANK, BLANK},
            {BLANK, {'>', MOB_COLOR_1},{'@', MOB_COLOR_2},{'>', MOB_COLOR_1}, BLANK},
            {BLANK, BLANK, BLANK, BLANK, BLANK}
        }
    },
    {//[3][][][]
        {//[3][0][][]
            {BLANK, BLANK, BLANK, BLANK, BLANK},
            {BLANK, {'/', MOB_COLOR_2}, {'\\', MOB_COLOR_2}, {'/', MOB_COLOR_1}, BLANK},
            {BLANK, {'\\', MOB_COLOR_2}, {'/', MOB_COLOR_2}, {'\\', MOB_COLOR_1}, BLANK}
        },
        {//[3][1][][]
            {BLANK, BLANK, BLANK, BLANK, BLANK},
            {BLANK, {'\\', MOB_COLOR_1}, {'/', MOB_COLOR_2}, {'\\', MOB_COLOR_2}, BLANK},
            {BLANK, {'/', MOB_COLOR_1}, {'\\', MOB_COLOR_2}, {'/', MOB_COLOR_2}, BLANK}
        }
    },
    {//[4][][][]
        {//[4][0][][]
            {BLANK, BLANK, BLANK, BLANK, BLANK},
            {BLANK, {'/', MOB_COLOR_2}, {'~', MOB_COLOR_2}, {'\\', MOB_COLOR_2}, {'/', MOB_COLOR_1}},
            {BLANK, {'\\', MOB_COLOR_2}, {'~', MOB_COLOR_2}, {'/', MOB_COLOR_2}, {'\\', MOB_COLOR_1}}
        },
        {//[4][1][][]
            {BLANK, BLANK, BLANK, BLANK, BLANK},
            {{'\\', MOB_COLOR_1}, {'/', MOB_COLOR_2}, {'~', MOB_COLOR_2}, {'\\', MOB_COLOR_2}, BLANK},
            {{'/', MOB_COLOR_1}, {'\\', MOB_COLOR_2}, {'~', MOB_COLOR_2}, {'/', MOB_COLOR_2}, BLANK}
        }
    },
    {//[5][][][]
        {//[5][0][][]
            {{'_', MOB_COLOR_2}, {'/', MOB_COLOR_2}, {'\\', MOB_COLOR_2}, {'_', MOB_COLOR_2}, {'/', MOB_COLOR_1}},
            {{'*', MOB_COLOR_1}, {'.', MOB_COLOR_1}, {'.', MOB_COLOR_1}, {'.', MOB_COLOR_1}, {'=', MOB_COLOR_1}},
            {{'\\', MOB_COLOR_2}, {'_', MOB_COLOR_2}, {'_', MOB_COLOR_2}, {'/', MOB_COLOR_2}, {'\\', MOB_COLOR_1}}
        },
        {//[5][1][][]
            {{'\\', MOB_COLOR_1}, {'_', MOB_COLOR_2}, {'/', COLOR_CYAN}, {'\\', MOB_COLOR_2}, {'_', MOB_COLOR_2}},
            {{'=', MOB_COLOR_1}, {'.', MOB_COLOR_1}, {'.', MOB_COLOR_1}, {'.', MOB_COLOR_1}, {'*', MOB_COLOR_1}},
            {{'/', MOB_COLOR_1}, {'\\', MOB_COLOR_2}, {'_', MOB_COLOR_2}, {'_', MOB_COLOR_2}, {'/', MOB_COLOR_2}}
        }
    }
};

#endif