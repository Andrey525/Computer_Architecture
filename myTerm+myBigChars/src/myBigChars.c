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

void Draw()
{
    mt_clrscr();
    int* rs = malloc(sizeof(int));
    int* cs = malloc(sizeof(int));

    mt_getscreensize(rs, cs);
    if (*rs < 30 || *cs < 100) {
        printf("Невозможно отрисовать интерфейс.\nУвеличьте размер окна терминала.\n");
        exit(-1);
    }
    int rows, cols;

    /** Заполняем память **/
    bc_box(5, 3, 11, 60);
    rows = 5;
    cols = 30;
    mt_gotoXY(rows, cols);
    printf(" Memory ");
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
    bc_box(5, 65, 2, 25);
    rows = 5;
    cols = 75;
    mt_gotoXY(rows, cols - 3);
    printf(" accumulator ");
    rows++;
    mt_gotoXY(rows, cols);
    printf("+9999");
    bc_box(8, 65, 2, 25);
    rows = rows + 2;
    mt_gotoXY(rows, cols - 6);
    printf(" instructionCounter ");
    rows++;
    mt_gotoXY(rows, cols);
    printf("+0000");
    bc_box(11, 65, 2, 25);
    rows = rows + 2;
    mt_gotoXY(rows, cols - 1);
    printf(" Operation ");
    rows++;
    mt_gotoXY(rows, cols - 1);
    printf("+00 : 00");
    bc_box(14, 65, 2, 25);
    rows = rows + 2;
    mt_gotoXY(rows, cols + 1);
    printf(" Flags ");
    rows++;
    mt_gotoXY(rows, cols - 1);
    printf("P O M T E");

    /** Заполняем Keys **/
    bc_box(17, 49, 9, 41);
    rows = rows + 2;
    cols = 50;
    mt_gotoXY(rows, cols);
    printf(" Keys: ");
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

    bc_box(17, 3, 9, 44);
    bc_printbigchar(plus, 18, 4, white, black);
    bc_printbigchar(nine, 18, 13, white, black);
    bc_printbigchar(nine, 18, 22, white, black);
    bc_printbigchar(nine, 18, 31, white, black);
    bc_printbigchar(nine, 18, 40, white, black);

    mt_gotoXY(35, 0);
}