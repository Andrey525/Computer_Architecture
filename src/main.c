#include "Draw.h"
#include "cpu.h"
#include "mysignal.h"

int main()
{
    srand(time(NULL));
    init();
    int value = 0;
    // for (int i = 0; i < SIZE_OF_MEMORY; i++) {
    //     value = (commands[(rand() % NUM_COMMANDS + 0)] << 7) | (rand() % 99 + 0);
    //     sc_memorySet(i, value);
    // }
    sc_commandEncode(0x30, 0, &value);
    sc_memorySet(0, value);
    sc_commandEncode(0x30, 1, &value);
    sc_memorySet(1, value);
    sc_commandEncode(0x30, 2, &value);
    sc_memorySet(2, value);
    sc_commandEncode(0x30, 3, &value);
    sc_memorySet(3, value);
    sc_commandEncode(0x31, 4, &value);
    sc_memorySet(4, value);
    sc_commandEncode(0x32, 5, &value);
    sc_memorySet(5, value);
    sc_commandEncode(0x33, 6, &value);
    sc_memorySet(6, value);
    sc_commandEncode(0x10, 99, &value);
    sc_memorySet(7, value);
    sc_commandEncode(0x11, 10, &value);
    sc_memorySet(8, value);
    sc_commandEncode(0x20, 17, &value);
    sc_memorySet(9, value);
    sc_commandEncode(0x21, 39, &value);
    sc_memorySet(10, value);
    sc_commandEncode(0x40, 13, &value);
    sc_memorySet(11, value);
    sc_commandEncode(0x42, 13, &value);
    sc_memorySet(12, value);
    sc_commandEncode(0x63, 13, &value);
    sc_memorySet(13, value);
    sc_commandEncode(0x43, 64, &value);
    sc_memorySet(14, value);

    sc_commandEncode(0x30, 0, &value);
    sc_memorySet(15, value);
    sc_commandEncode(0x30, 1, &value);
    sc_memorySet(16, value);
    sc_commandEncode(0x30, 2, &value);
    sc_memorySet(17, value);
    sc_commandEncode(0x30, 3, &value);
    sc_memorySet(18, value);
    sc_commandEncode(0x31, 4, &value);
    sc_memorySet(19, value);
    sc_commandEncode(0x32, 5, &value);
    sc_memorySet(20, value);
    sc_commandEncode(0x33, 6, &value);
    sc_memorySet(21, value);
    sc_commandEncode(0x10, 99, &value);
    sc_memorySet(22, value);
    sc_commandEncode(0x11, 98, &value);
    sc_memorySet(23, value);
    sc_commandEncode(0x20, 97, &value);
    sc_memorySet(24, value);
    sc_commandEncode(0x21, 96, &value);
    sc_memorySet(25, value);
    sc_commandEncode(0x40, 30, &value);
    sc_memorySet(26, value);
    sc_commandEncode(0x42, 64, &value);
    sc_memorySet(27, value);
    sc_commandEncode(0x63, 64, &value);
    sc_memorySet(28, value);
    sc_commandEncode(0x43, 64, &value);
    sc_memorySet(29, value);
    sc_commandEncode(0x65, 0, &value);
    sc_memorySet(90, value);

    signal(SIGALRM, my_timer);
    signal(SIGUSR1, my_signal);
    struct itimerval nval, oval;
    nval.it_interval.tv_sec = 1;
    nval.it_interval.tv_usec = 0;
    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &nval, &oval);
    while (key != KEY_Q) {
        Draw();
        sc_regGet(T, &value);
        rk_readKey(&key);
        if (value == 1) {
            switch (key) {
            case KEY_UP:
                alarm(0);
                K_UP();
                break;
            case KEY_DOWN:
                alarm(0);
                K_DOWN();
                break;
            case KEY_RIGHT:
                alarm(0);
                K_RIGHT();
                break;
            case KEY_LEFT:
                alarm(0);
                K_LEFT();
                break;
            case KEY_F5:
                alarm(0);
                F5();
                break;
            case KEY_F6:
                alarm(0);
                F6();
                break;
            case KEY_L:
                alarm(0);
                load();
                break;
            case KEY_S:
                alarm(0);
                save();
                break;
            case KEY_R:
                alarm(0);
                sc_regSet(T, 0);
                setitimer(ITIMER_REAL, &nval, &oval);
                break;
            case KEY_T:
                alarm(0);
                CU();
                break;
            case KEY_I:
                break;
            case KEY_Q:
                // break while
                // alarm(0);
                break;
            case KEY_ENTER:
                alarm(0);
                K_ENTER();
                break;
            case KEY_OTHER:
                break;
            }
        } else {
            if (key == KEY_I) {
                alarm(0);
                raise(SIGUSR1);
                sc_regSet(T, 1);
            }
        }
    }
    return 0;
}
