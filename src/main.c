#include "Draw.h"

int main()
{
    srand(time(NULL));
    init();
    for (int i = 0; i < SIZE_OF_MEMORY; i++) {
        // sc_memorySet(i, rand() % 16383);
        sc_memorySet(i, rand() % 32768);
    }
    while (key != KEY_Q) {
        Draw();
        rk_readKey(&key);
        switch (key) {
        case KEY_UP:
            K_UP();
            break;
        case KEY_DOWN:
            K_DOWN();
            break;
        case KEY_RIGHT:
            K_RIGHT();
            break;
        case KEY_LEFT:
            K_LEFT();
            break;
        case KEY_F5:
            F5();
            break;
        case KEY_F6:
            F6();
            break;
        case KEY_L:
            load();
            break;
        case KEY_S:
            save();
            break;
        case KEY_R:
            break;
        case KEY_T:
            break;
        case KEY_I:
            init();
            break;
        case KEY_Q:
            // break while
            break;
        case KEY_ENTER:
            K_ENTER();
            break;
        case KEY_OTHER:
            break;
        }
    }
    return 0;
}
