#include "mysignal.h"

void my_timer(int signo)
{
    int value;
    sc_regGet(T, &value);
    if (value == 0 && instructionCounter < 99) {
        num_element = instructionCounter;
        move(0);
        instructionCounter++;
        num_element = instructionCounter;
        move(1);
    }
    Draw();
}

void my_signal(int signo)
{
    init();
}
