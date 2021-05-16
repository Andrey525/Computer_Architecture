#include "mysignal.h"
#include "cpu.h"

void my_timer(int signo)
{
    int value;
    sc_regGet(T, &value);
    if (value == 0 && instructionCounter < 99) {
        CU();
    } else if (value == 1) {
        alarm(0);
    }
    Draw();
}

void my_signal(int signo)
{
    init();
}
