#ifndef MY_BIG_CHARS_H
#define MY_BIG_CHARS_H

#include <stdio.h>

#define ANGLE_LEFT_BOTTOM "m"
#define ANGLE_LEFT_TOP "l"
#define ANGLE_RIGHT_BOTTOM "j"
#define ANGLE_RIGHT_TOP "k"
#define LINE_HORIZONTAL "q"
#define LINE_VERTICAL "x"
#define CUBE "a"

int bc_printA(char* str);
int bc_box(int x1, int y1, int x2, int y2);

#endif
