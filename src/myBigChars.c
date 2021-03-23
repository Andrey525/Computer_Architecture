#include "myBigChars.h"
#include "mySimpleComputer.h"
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
long int a[2] = { 1111638654, 1111630872 };
long int b[2] = { 1044529730, 1044529726 };
long int c[2] = { 2114060802, 33686142 };
long int d[2] = { 1044529730, 1111638590 };
long int e[2] = { 2114060802, 2114060926 };
long int f[2] = { 33686018, 1040319102 };
long int plus[2] = { 404232447, 4279769112 };
long int minus[2] = { 255, 4278190080 };

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

int bc_setbigcharpos(long int* digit, int x, int y, int value)
{
    if (value > 1 || value < 0 || x > 7 || x < 0 || y > 7 || y < 0) {
        return -1;
    }

    int index = 1;

    if (x > 3) {
        index = 0;
    }

    if (value == 1) {
        digit[index] = digit[index] | 1 << (x * 8 + y);
    } else {
        digit[index] = digit[index] & ~(1 << (x * 8 + y));
    }
    return 0;
}

int bc_getbigcharpos(long int* digit, int x, int y, int* value)
{
    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return -1;
    }

    int index = 1;

    if (x > 3) {
        index = 0;
    }

    *value = ((digit[index] >> (x * 8 + y)) & 1);

    return 0;
}

int bc_bigcharwrite(int fd, long int* digit, int count)
{
    if (!digit || fd < 0) {
        return -1;
    }

    while (count > 0) {
        int result;
        if ((result = write(fd, digit, sizeof(long int) * 2)) == -1)
            return -1;
        count--;
    }

    return 0;
}

int bc_bigcharread(int fd, long int* digit, int need_count, int* count)
{
    if (fd < 0)
        return -1;

    while (need_count > 0) {
        int result;
        if ((result = read(fd, digit, sizeof(long int) * 2)) == -1)
            return -1;

        need_count--;
        *count = *count + 1;
    }

    return 0;
}
