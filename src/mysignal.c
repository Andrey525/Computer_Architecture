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
    //     int value = 0;
    //     sc_regGet(IGNR_TIME, &value);
    //     if (instructionCounter < 99 && !value) {
    //         instructionCounter++;
    //     }
    //     sc_regGet(IGNR_PULSES, &value);
    //     if (!value) {
    //         while (value == 0) {
    //             // _print_screen_();
    //             value = CU();
    //             sleep(1);
    //         }
    //         if (value == 2) {
    //             sc_regSet(IGNR_PULSES, 1);
    //             alarm(0);
    //         }
    //     } else {
    //         alarm(0);
    //     }
    //     // _print_screen_();
}

void my_signal(int signo)
{
    init();
}
