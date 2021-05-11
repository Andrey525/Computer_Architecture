#include "mySimpleComputer.h"

const int commands[NUM_COMMANDS] = { 0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40, 0x41, 0x42, 0x43,
    0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76 };

int sc_memoryInit()
{
    for (int i = 0; i < SIZE_OF_MEMORY; i++) {
        RAM[i] = 0;
    }
    return 0;
}

int sc_memorySet(int adress, int value)
{
    if (adress < 0 || adress >= SIZE_OF_MEMORY) {
        sc_regSet(M, 1);
        return ERROR_EXIT_RANGE_ARRAY;
    }
    RAM[adress] = value;
    return 0;
}

int sc_memoryGet(int adress, int* value)
{
    if (adress < 0 || adress >= SIZE_OF_MEMORY) {
        sc_regSet(M, 1);
        return ERROR_EXIT_RANGE_ARRAY;
    }
    *value = RAM[adress];
    return 0;
}

int sc_memorySave(char* filename)
{
    FILE* file;
    if ((file = fopen(filename, "wb")) == NULL) {
        return ERROR_FWRITE; // ошибка записи в файл
    }
    fwrite(RAM, sizeof(int), SIZE_OF_MEMORY, file);
    fclose(file);
    return 0;
}

int sc_memoryLoad(char* filename)
{
    FILE* file;
    if ((file = fopen(filename, "rb")) == NULL) {
        return ERROR_FREAD; // ошибка чтения из файла
    }
    if (fread(RAM, sizeof(int), SIZE_OF_MEMORY, file) != SIZE_OF_MEMORY) {
        if (feof(file)) {
            return ERROR_FEOF;
        } else {
            return ERROR_FREAD;
        }
    }
    return 0;
}

int sc_regInit()
{
    registr_of_flags = 0;
    return 0;
}

int sc_regSet(int registr, int value)
{
    if (((value == 1) || (value == 0)) == false) { // проверка на допустимое значение
        return ERROR_VALUE;
    }
    if ((registr == P || registr == O || registr == M || registr == T || registr == E) == false) { // проверка на допустимый номер регистра
        return ERROR_RANK;
    }
    if (value == 1) {
        registr_of_flags = registr_of_flags | registr;
    } else if (value == 0) {
        registr_of_flags = registr_of_flags & (~registr);
    }
    return 0;
}

int sc_regGet(int registr, int* value)
{
    if ((registr == P || registr == O || registr == M || registr == T || registr == E) == false) { // проверка на допустимый разряд
        return ERROR_RANK;
    }
    if ((registr_of_flags & registr) != 0) {
        *value = 1;
    } else {
        *value = 0;
    }

    return 0;
}

int sc_commandEncode(int command, int operand, int* value)
{
    if (command < 0x10 || (command > 0x11 && command < 0x20) || (command > 0x21 && command < 0x30) || (command > 0x33 && command < 0x40) || (command > 0x43 && command < 0x51) || command > 0x76) {
        return ERROR_INVALID_COMMAND;
    }
    if (operand > 0x7F || operand < 0) {
        return ERROR_INVALID_OPERAND;
    }

    *value = (command << 7) | operand;

    return 0;
}

int sc_commandDecode(int value, int* command, int* operand)
{
    int attribute;
    int temp_command, temp_operand;
    attribute = value & 0x4000;
    if (attribute != 0) {
        return ERROR_NOT_COMMAND;
    }
    temp_operand = value & 0x7F;
    temp_command = (value >> 7) & 0x7F;
    if (temp_command < 0x10 || (temp_command > 0x11 && temp_command < 0x20) || (temp_command > 0x21 && temp_command < 0x30) || (temp_command > 0x33 && temp_command < 0x40) || (temp_command > 0x43 && temp_command < 0x51) || temp_command > 0x76) {
        sc_regSet(E, 1);
        return ERROR_INVALID_COMMAND;
    }
    // sc_regSet(E, 0);
    *operand = temp_operand;
    *command = temp_command;
    return 0;
}