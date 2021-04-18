#ifndef MYREADKEY_H
#define MYREADKEY_H
// #include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>

enum keys {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_F5,
    KEY_F6,
    KEY_L,
    KEY_S,
    KEY_R,
    KEY_T,
    KEY_I,
    KEY_Q,
    KEY_ENTER,
    KEY_OTHER
};

struct termios options;
struct termios stock_options;
enum keys key;

int rk_readKey(enum keys* key);
int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif