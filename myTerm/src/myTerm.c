#include "myTerm.h"

int mt_clrscr()
{
    printf("\E[H\E[J");
    return 0;
}

int mt_gotoXY(int row, int col)
{
    printf("\E[%d;%dH", row, col);
    return 0;
}

int mt_getscreensize(int* rows, int* cols)
{
    struct winsize ws;
    if (!ioctl(1, TIOCGWINSZ, &ws)) {
        *rows = ws.ws_row;
        *cols = ws.ws_col;
    } else
        return -1;
    return 0;
}

int mt_setfgcolor(enum colors color)
{
    if (color < 0 || color > 7) {
        return -1;
    }
    printf("\E[3%dm", color);
    return 0;
}

int mt_setbgcolor(enum colors color)
{
    if (color < 0 || color > 7) {
        return -1;
    }
    printf("\E[4%dm", color);
    return 0;
}

int mt_setdefaultcolor()
{
    printf("\E[0m");
    return 0;
}

void Draw()
{
    mt_clrscr();
    int rows, cols;

    /** Заполняем память **/
    rows = 5;
    cols = 30;
    mt_gotoXY(rows, cols);
    printf("Memory");
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        rows++;
        mt_gotoXY(rows, 4);
        for (int j = 0; j < 10; j++) {
            int value = rand() % 65535;
            printf("+%04x ", value);
        }
    }

    /** Заполняем правую часть **/
    rows = 5;
    cols = 75;
    mt_gotoXY(rows, cols - 3);
    printf("accumulator");
    rows++;
    mt_gotoXY(rows, cols);
    printf("+9999");
    rows = rows + 2;
    mt_gotoXY(rows, cols - 6);
    printf("instructionCounter");
    rows++;
    mt_gotoXY(rows, cols);
    printf("+0000");
    rows = rows + 2;
    mt_gotoXY(rows, cols - 1);
    printf("Operation");
    rows++;
    mt_gotoXY(rows, cols - 1);
    printf("+00 : 00");
    rows = rows + 2;
    mt_gotoXY(rows, cols + 1);
    printf("Flags");
    rows++;
    mt_gotoXY(rows, cols - 1);
    printf("P O M T E");

    /** Заполняем Keys **/

    rows = rows + 2;
    cols = 50;
    mt_gotoXY(rows, cols);
    printf("Keys:");
    rows++;
    mt_gotoXY(rows, cols);
    printf("l  - load");
    rows++;
    mt_gotoXY(rows, cols);
    printf("s  - save");

    rows++;
    mt_gotoXY(rows, cols);
    printf("r  - run");

    rows++;
    mt_gotoXY(rows, cols);
    printf("t  - step");

    rows++;
    mt_gotoXY(rows, cols);
    printf("i  - reset");

    rows++;
    mt_gotoXY(rows, cols);
    printf("f5 - accumulator");

    rows++;
    mt_gotoXY(rows, cols);
    printf("f6 - instructionCounter");

    mt_gotoXY(35, 0);
}