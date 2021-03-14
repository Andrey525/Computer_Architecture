#include "myBigChars.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

int main()
{
    sc_memoryInit();
    sc_regInit();
    srand(time(NULL));
    int value;
    for (int i = 0; i < SIZE_OF_MEMORY; i++) {
        sc_commandEncode(0x32, i, &value);
        sc_memorySet(i, value);
    }
    instructionCounter = 98;
    sc_memorySet(instructionCounter, 10594);
    sc_regSet(P, 1);
    // sc_regSet(O, 1);
    sc_regSet(M, 1);
    sc_regSet(T, 1);
    // sc_regSet(E, 1);
    Draw();
    return 0;
}
