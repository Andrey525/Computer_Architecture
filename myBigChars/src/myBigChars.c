#include "myBigChars.h"

int bc_printA(char* str)
{
    printf("\E(0%s\E(B", str);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
    return 0;
}
