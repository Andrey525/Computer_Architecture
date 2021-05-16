#include "cpu.h"

int ALU(int command, int operand)
{
    int value; // помещаем сюда значение из ячейки памяти, на которую указывает операнд
    if (sc_memoryGet(operand, &value) == ERROR_EXIT_RANGE_ARRAY) {
        return 1;
    }
    if (command < 0x30 || command > 0x33) { // возможно лишняя часть кода
        return 1;
    }
    if (command == 0x30) {
        if ((accumulator + value) >= 0xffff) { // ADD
            sc_regSet(P, 1); // устанавливаем флаг - переполнение при выполнение операции
            return 1;
        }
        accumulator += value;
    } else if (command == 0x31) {
        if ((accumulator - value) < -0xffff) { // SUB
            sc_regSet(P, 1);
            return 1;
        }
        accumulator -= value;
    } else if (command == 0x32) {
        if (value == 0x0) { // DIVIDE
            sc_regSet(O, 1); // устанавливаем флаг - ошибка деления на ноль
            return 1;
        }
        accumulator /= value;
    } else if (command == 0x33) {
        if ((accumulator * value) >= 0xffff) { // MUL
            sc_regSet(P, 1);
            return 1;
        }
        accumulator *= value;
    }
    return 0;
}

int CU()
{
    int command = 0, operand = 0, value = 0;
    if (sc_commandDecode(RAM[instructionCounter], &command, &operand)) {
        sc_regSet(T, 1);
        return 1;
    }
    if (operand < 0 || operand >= SIZE_OF_MEMORY) {
        sc_regSet(M, 1);
        return 1;
    }
    if (command > 0x33 || command < 0x30) {
        if (command == 0x10) { // READ
            mt_gotoXY((operand / 10) + 6, (operand % 10) * 6 + 4);
            printf("     ");
            mt_gotoXY((operand / 10) + 6, (operand % 10) * 6 + 4);
            // rk_mytermregime(1, 1, 1, 1, 1);
            scanf("%4x", &value);
            // rk_mytermrestore();
            if (value < 0xffff) {
                sc_memorySet(operand, value);
            } else {
                sc_memorySet(operand, 0xffff);
                sc_regSet(P, 1);
            }
        } else if (command == 0x11) { // WRITE
            mt_gotoXY(30, 0);
            sc_memoryGet(operand, &value);
            printf("value = %x\n", value);
            sleep(1);
        } else if (command == 0x20) { // LOAD
            sc_memoryGet(operand, &accumulator);
        } else if (command == 0x21) { // STORE
            if (accumulator < 0xffff) {
                sc_memorySet(operand, accumulator);
            } else {
                sc_memorySet(operand, 0xffff);
                sc_regSet(P, 1);
            }
        } else if (command == 0x40) { // JUMP
            if (operand > 99) {
                sc_regSet(M, 1);
            } else {
                instructionCounter = operand;
                return 0;
            }
        } else if (command == 0x41) { // JNEG
            if (accumulator < 0) {
                instructionCounter = operand;
                return 0;
            }
        } else if (command == 0x42) { // JZ
            if (accumulator == 0) {
                instructionCounter = operand;
                return 0;
            }
        } else if (command == 0x43) { // HALT
            sc_regSet(T, 1);
            return 1;
        } else if (command == 0x65) { // ADDC
            sc_memoryGet(operand, &value); // получаем значение указанной ячейки памяти
            operand = accumulator & 0x7F; // получаем адрес ячейки памяти, на которую указывает аккумулятор
            if (operand < 0 || operand >= SIZE_OF_MEMORY) {
                sc_regSet(M, 1);
                return 1;
            }
            accumulator = value; // записываем значение указанной ячейки памяти в аккумулятор
            sc_memoryGet(operand, &value); // получаем значение ячейки памяти, адрес которой находился в аккумкуляторе
            accumulator += value; // результат сложения
        }
    } else {
        if (ALU(command, operand)) {
            return 1;
        }
    }
    if (instructionCounter != 99) {
    	instructionCounter++;
	}
    return 0;
}
