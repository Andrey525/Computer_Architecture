#include "Draw.h"

void init()
{
    sc_memoryInit();
    sc_regInit();
    instructionCounter = 0;
    accumulator = 0;
    num_element = 0;
    sc_regSet(T, 1);
#if 1
    int value;
    for (int i = 0; i < SIZE_OF_MEMORY; i++) {
        value = (commands[(rand() % NUM_COMMANDS + 0)] << 7) | (rand() % 99 + 0);
        sc_memorySet(i, value);
    }
#endif
}

void move(int i)
{
    int rows = 6, cols = 4;

    rows += num_element / 10;
    cols += num_element % 10 * 6;
    mt_gotoXY(rows, cols);
    if (i == 1) {
        mt_setbgcolor(white);
        mt_setfgcolor(black);
    } else {
        mt_setdefaultcolor();
    }
    // int value;
    // sc_memoryGet(num_element, &value);
    // int attribute = value & 0x4000;
    // if (attribute == 0) {
    printf("+%04x", RAM[num_element]);
    // } else {
    // printf("-%04x", RAM[num_element]);
    // }
    mt_setdefaultcolor();
}

void K_UP()
{
    if (num_element > 9) {
        move(0);
        num_element -= 10;
        move(1);
    }
}

void K_DOWN()
{
    if (num_element < 90) {
        move(0);
        num_element += 10;
        move(1);
    }
}

void K_RIGHT()
{
    if (num_element % 10 != 9) {
        move(0);
        num_element++;
        move(1);
    }
}

void K_LEFT()
{
    if (num_element % 10 != 0) {
        move(0);
        num_element--;
        move(1);
    }
}

void clean_input()
{
    int rows, cols;
    mt_getscreensize(&rows, &cols);
    for (int i = 30; i <= 31; i++) {
        for (int j = 1; j < cols; j++) {
            mt_gotoXY(i, j);
            printf(" ");
        }
    }
}

void save()
{
    char* filename = malloc(sizeof(char) * 20);
    mt_gotoXY(30, 1);
    printf("File name for save RAM values: ");
    scanf("%s", filename);
    sc_memorySave(filename);
    sleep(1);
    clean_input();
}

void load()
{
    char* filename = malloc(sizeof(char) * 20);
    mt_gotoXY(30, 1);
    printf("File name for load RAM values: ");
    scanf("%s", filename);
    sc_memoryLoad(filename);
    sleep(1);
    clean_input();
}

void F5()
{
    sc_memoryGet(num_element, &accumulator);
}
void F6()
{
    instructionCounter = num_element;
}

void K_ENTER()
{
    int rows = 6, cols = 4;
    rows += num_element / 10;
    cols += num_element % 10 * 6;
    mt_gotoXY(rows, cols);
    printf("     ");
    mt_gotoXY(rows, cols);
    int value = 0;
    scanf("%4x", &value);
    sc_memorySet(num_element, value);
}

void Draw()
{
    mt_clrscr();
    int* rs = malloc(sizeof(int));
    int* cs = malloc(sizeof(int));
    int value;
    int command = 0, operand = 0;
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
            // sc_memoryGet(i * 10 + j, &value);
            // int attribute = value & 0x4000;
            // if (attribute == 0) {
            printf("+%04x ", RAM[i * 10 + j]);
            // } else {
            // printf("-%04x ", RAM[i * 10 + j]);
            // }
        }
    }
    move(1);
    /** Заполняем правую часть **/
    bc_box(5, 65, 2, 25);
    rows = 5;
    cols = 75;
    mt_gotoXY(rows, cols - 3);
    printf(" accumulator ");
    rows++;
    mt_gotoXY(rows, cols);
    // int attribute;
    // attribute = accumulator & 0x4000;
    // if (attribute == 0) {
    printf("+%04x", accumulator);
    // } else {
    // printf("-%04x", accumulator);
    // }

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

    command = 0, operand = 0;

    sc_memoryGet(instructionCounter, &value);
    sc_commandDecode(value, &command, &operand);
    // if (sc_commandDecode(value, &command, &operand) == ERROR_NOT_COMMAND) {
    // printf("-%02x : %02x", command, operand);
    // } else {
    printf("+%02x : %02x", command, operand);
    // }
    bc_box(14, 65, 2, 25);
    rows = rows + 2;
    mt_gotoXY(rows, cols + 1);
    printf(" Flags ");
    rows++;
    mt_gotoXY(rows, cols - 1);
    value = 0;
    if (sc_regGet(P, &value) == 0) {
        if (value == 1) {
            printf("P ");
            value = 0;
        } else {
            printf("  ");
        }
    }
    if (sc_regGet(O, &value) == 0) {
        if (value == 1) {
            printf("O ");
            value = 0;
        } else {
            printf("  ");
        }
    }
    if (sc_regGet(M, &value) == 0) {
        if (value == 1) {
            printf("M ");
            value = 0;
        } else {
            printf("  ");
        }
    }
    if (sc_regGet(T, &value) == 0) {
        if (value == 1) {
            printf("T ");
            value = 0;
        } else {
            printf("  ");
        }
    }
    if (sc_regGet(E, &value) == 0) {
        if (value == 1) {
            printf("E ");
            value = 0;
        } else {
            printf("  ");
        }
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
    printf("t  - step  (in developing)");

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
    // if (sc_commandDecode(value, &command, &operand) == ERROR_NOT_COMMAND) {
    // bc_printbigchar(minus, 18, 4, white, black);
    // } else {
    bc_printbigchar(plus, 18, 4, white, black);
    // }
    cols = 4 + 9;
    for (int i = 3; i >= 0; i--) {
        if (((value >> 4 * i) & 15) == 0x0) {
            bc_printbigchar(zero, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0x1) {
            bc_printbigchar(one, 18, cols, white, black);
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
        } else if (((value >> 4 * i) & 15) == 0xA) {
            bc_printbigchar(a, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0xB) {
            bc_printbigchar(b, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0xC) {
            bc_printbigchar(c, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0xD) {
            bc_printbigchar(d, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0xE) {
            bc_printbigchar(e, 18, cols, white, black);
        } else if (((value >> 4 * i) & 15) == 0xF) {
            bc_printbigchar(f, 18, cols, white, black);
        }
        cols = cols + 9;
    }
    mt_gotoXY(27, 4);
    printf("Input/Output\n");

    mt_gotoXY(30, 0);
}
