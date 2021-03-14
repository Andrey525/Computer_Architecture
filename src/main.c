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
    instructionCounter = 95;
    sc_memorySet(instructionCounter, 0x3B5F);
    sc_regSet(P, 1);
    // sc_regSet(O, 1);
    sc_regSet(M, 1);
    sc_regSet(T, 1);
    // sc_regSet(E, 1);
    Draw();
    // bc_printbigchar(a, 20, 20, white, black);
    // bc_printbigchar(b, 20, 30, white, black);
    // bc_printbigchar(c, 20, 40, white, black);
    // bc_printbigchar(d, 20, 50, white, black);
    // bc_printbigchar(e, 20, 60, white, black);
    // bc_printbigchar(f, 20, 70, white, black);
    return 0;
}
