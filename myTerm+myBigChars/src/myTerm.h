#ifndef MY_TERM_H
#define MY_TERM_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/*

clear_screen=\E[H\E[J
cursor_address=\E[%i%p1%d;%p2%dH
cursor_invisible=\E[?25l\E[?1c
cursor_visible=\E[?25h\E[?8c
set_a_background=\E[4%p1%dm
set_a_foreground=\E[3%p1%dm

*/

enum colors {
    black = 0,
    red = 1,
    green = 2,
    yellow = 3,
    blue = 4,
    pink = 5,
    lightblue = 6,
    white = 7,
};

int mt_clrscr();
int mt_gotoXY(int row, int col);
int mt_getscreensize(int* rows, int* cols);
int mt_setfgcolor(enum colors color);
int mt_setbgcolor(enum colors color);
int mt_setdefaultcolor();

#endif
