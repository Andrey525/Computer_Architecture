#include "myBigChars.h"
#include "myTerm.h"

int bc_printA(char* str)
{
    printf("\E(0%s\E(B", str);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
    mt_gotoXY(x1, y1);
    bc_printA("l"); // левый верхний угол выводим
    mt_gotoXY(x1 + x2, y1);
    bc_printA("m");
    for (int i = 1; i <= y2; i++) {
        mt_gotoXY(x1, y1 + i);
        bc_printA("q");
        if (i == y2) {
            bc_printA("k");
        }
        mt_gotoXY(x1 + x2, y1 + i);
        bc_printA("q");
        if (i == y2) {
            bc_printA("j");
        }
    }
    for (int i = 1; i < x2; i++) {
        mt_gotoXY(x1 + i, y1);
        bc_printA("x");
        mt_gotoXY(x1 + i, y1 + y2 + 1);
        bc_printA("x");
    }
    mt_gotoXY(x1 + x2 + 2, 0);
    return 0;
}
