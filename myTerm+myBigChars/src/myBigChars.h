#ifndef MY_BIG_CHARS_H
#define MY_BIG_CHARS_H

#include "myTerm.h"
#include <stdio.h>

#define ANGLE_LEFT_BOTTOM "m"
#define ANGLE_LEFT_TOP "l"
#define ANGLE_RIGHT_BOTTOM "j"
#define ANGLE_RIGHT_TOP "k"
#define LINE_HORIZONTAL "q"
#define LINE_VERTICAL "x"
#define CUBE "a"

extern long int zero[2];
extern long int one[2];
extern long int two[2];
extern long int three[2];
extern long int four[2];
extern long int five[2];
extern long int six[2];
extern long int seven[2];
extern long int eight[2];
extern long int nine[2];
extern long int plus[2];

int bc_printA(char* str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(long int* digit, int x, int y, enum colors fgcolor, enum colors bgcolor);

#endif
