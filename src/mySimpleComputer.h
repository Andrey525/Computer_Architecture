#include <stdbool.h>
#include <stdio.h>

#ifndef COMP_H
#define COMP_H
#define SIZE_OF_MEMORY 100

/* МАСКИ ДЛЯ РЕГИСТРА ФЛАГОВ */
#define P 0b00000001 // переполнение при выполнение операции
#define O 0b00000010 // ошибка деления на 0
#define M 0b00000100 // ошибка выхода за границы памяти
#define T 0b00001000 // игнорирование тактовых импульсов
#define E 0b00010000 // указана неверная команда
/***************************************************************************/

// #define BIT_CHECK(REG, RANK) ((REG >> RANK) & 0x1) // получить флаг
// #define BIT_SET(REG, RANK) ((REG = ((REG) | (0x1 << RANK)))) // установить 1
// #define BIT_DELETE(REG, RANK) (REG = ((REG) & (~(0x1 << RANK)))) // установить 0

#define ERROR_EXIT_RANGE_ARRAY -1 // Ошибка выхода за границы массива
#define ERROR_FWRITE -2 // Ошибка записи в файл (файл не открылся)
#define ERROR_FREAD -3 // Ошибка чтения из файла
#define ERROR_FEOF -4 // Ошибка: преждевременный конец файла
#define ERROR_VALUE -5 // Ошибка: недопустимое значение
#define ERROR_RANK -6 // Ошибка: недопустимый разряд регистра
#define ERROR_INVALID_COMMAND -7 // Ошибка: неверная команда
#define ERROR_INVALID_OPERAND -8 // Ошибка: неверный операнд
#define ERROR_NOT_COMMAND -9 // Ошибка: это не команда

int RAM[SIZE_OF_MEMORY];
int registr_of_flags; // регистр флагов(переменная хранящая флаги)
int instructionCounter; // счетчик команд (номер ячейки памяти, в которой находится текущая выполняемая команда)
int accumulator; // 

int sc_memoryInit();
int sc_memorySet(int adress, int value);
int sc_memoryGet(int adress, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit();
int sc_regSet(int registr, int value);
int sc_regGet(int registr, int* value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);

#endif