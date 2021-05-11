#include "mysignal.h"
#include "cpu.h"

void my_timer(int signo)
{
    int value;
    sc_regGet(T, &value);
    if (value == 0 && instructionCounter < 99) {
        move(0);
        CU();
        move(1);
    }
    Draw();
}

void my_signal(int signo)
{
    init();
}
