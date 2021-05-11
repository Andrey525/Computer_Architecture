#ifndef DRAW_H
#define DRAW_H
#include "myBigChars.h"
#include "myReadkey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

void init();
void clean_input();
void save();
void load();
void move(int i);
void K_UP();
void K_DOWN();
void K_RIGHT();
void K_LEFT();
void K_ENTER();
void F5();
void F6();
void Draw();

#endif