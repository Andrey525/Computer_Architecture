#include "Draw.h"

int main()
{
    init();
    sc_memorySet(12, 0x3B5F);
    sc_memorySet(18, 0x3B5F);
    sc_memorySet(67, 0x3B5F);
    sc_memorySet(45, 0x3B5F);
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
            init();
            break;
        case KEY_T:
            break;
        case KEY_I:
            break;
        case KEY_Q:
            // break while
            break;
        case KEY_ENTER:
            break;
        case KEY_OTHER:
            break;
        }
    }
    return 0;
}
