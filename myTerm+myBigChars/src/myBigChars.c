#include "myBigChars.h"
#include "myTerm.h"

long int zero[2] = { 4291019715, 3284386815 };
long int one[2] = { 4279769112, 404626456 };
long int two[2] = { 4278586392, 811647870 };
long int three[2] = { 2126733360, 811647870 };
long int four[2] = { 1616969571, 1718384752 };
long int five[2] = { 4290822336, 4278387711 };
long int six[2] = { 4291019715, 4278387711 };
long int seven[2] = { 50727960, 811647231 };
long int eight[2] = { 4291019715, 4291019775 };
long int nine[2] = { 4290822399, 3284386815 };
long int plus[2] = { 404232447, 4279769112 };

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
    // mt_gotoXY(x1 + x2 + 2, 0);
    return 0;
}

int bc_printbigchar(long int* digit, int x, int y, enum colors fgcolor, enum colors bgcolor)
{
    mt_setfgcolor(fgcolor);
    mt_setbgcolor(bgcolor);
    mt_gotoXY(x, y);
    for (int j = 1; j != -1; j--) {
        for (int byte = 0; byte < 4; byte++) {
            for (int bit = 0; bit < 8; bit++) {
                if (((digit[j] >> (bit + (byte * 8))) & 0x1) == 0x1) {
                    bc_printA(CUBE);
                } else {
                    printf(" ");
                }
            }
            x++;
            mt_gotoXY(x, y);
        }
    }
    mt_setdefaultcolor();
    return 0;
}