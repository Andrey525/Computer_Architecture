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

    for (int i = 0; i < 10; i++) {
        rows++;
        mt_gotoXY(rows, 4);
        for (int j = 0; j < 10; j++) {
            // int value = rand() % 65535;
            // printf("+%04x ", value);
            printf("+%04x ", RAM[i * 10 + j]);
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
    int value;
    sc_memoryGet(instructionCounter, &value);
    printf("+%0x", value);
    bc_box(8, 65, 2, 25);
    rows = rows + 2;
    mt_gotoXY(rows, cols - 6);
    printf(" instructionCounter ");
    rows++;
    mt_gotoXY(rows, cols);
    printf("+%04x", instructionCounter);
    bc_box(11, 65, 2, 25);
    rows = rows + 2;
    mt_gotoXY(rows, cols - 1);
    printf(" Operation ");
    rows++;
    mt_gotoXY(rows, cols - 1);

    int command = 0, operand = 0;

    sc_memoryGet(instructionCounter, &value);
    sc_commandDecode(value, &command, &operand);
    printf("+%x : %x", command, operand);
    bc_box(14, 65, 2, 25);
    rows = rows + 2;
    mt_gotoXY(rows, cols + 1);
    printf(" Flags ");
    rows++;
    mt_gotoXY(rows, cols - 1);
    if ((registr_of_flags & P) != 0) {
        printf("P ");
    } else {
        printf("  ");
    }
    if ((registr_of_flags & O) != 0) {
        printf("O ");
    } else {
        printf("  ");
    }
    if ((registr_of_flags & M) != 0) {
        printf("M ");
    } else {
        printf("  ");
    }
    if ((registr_of_flags & T) != 0) {
        printf("T ");
    } else {
        printf("  ");
    }
    if ((registr_of_flags & E) != 0) {
        printf("E ");
    } else {
        printf("  ");
    }

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
    sc_memoryGet(instructionCounter, &value);

    bc_printbigchar(plus, 18, 4, white, black);
    cols = 4 + 9;
    for (int i = 3; i >= 0; i--) {
        if (((value >> 4 * i) & 15) == 0x0) {
            bc_printbigchar(zero, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0x1) {
            bc_printbigchar(two, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0x2) {
            bc_printbigchar(two, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0x3) {
            bc_printbigchar(three, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0x4) {
            bc_printbigchar(four, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0x5) {
            bc_printbigchar(five, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0x6) {
            bc_printbigchar(six, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0x7) {
            bc_printbigchar(seven, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0x8) {
            bc_printbigchar(eight, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0x9) {
            bc_printbigchar(nine, 18, cols, white, black);
        }
        cols = cols + 9;
    }
    // bc_printbigchar(nine, 18, 13, white, black);
    // bc_printbigchar(nine, 18, 22, white, black);
    // bc_printbigchar(nine, 18, 31, white, black);
    // bc_printbigchar(nine, 18, 40, white, black);

    mt_gotoXY(35, 0);
}