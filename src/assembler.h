#include "mySimpleComputer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef ASSEMBLER_H
#define ASSEMBLER_H
int find_pref(char* ar, int arg);
int get_command(char* str);
int write_into_memory(char* str);
int assembler_to_simple_computer(char* from, char* to);

#endif
