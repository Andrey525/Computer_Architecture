#include "Draw.h"
#include "mysignal.h"

int main()
{
    srand(time(NULL));
    init();
    int value = 0;
    for (int i = 0; i < SIZE_OF_MEMORY; i++) {
        value = (commands[(rand() % NUM_COMMANDS + 0)] << 7) | (rand() % 99 + 0);
        sc_memorySet(i, value);
    }
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
                move(0);
                num_element = instructionCounter;
                move(1);
                sc_regSet(T, 0);
                setitimer(ITIMER_REAL, &nval, &oval);
                break;
            case KEY_T:
                alarm(0);
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
