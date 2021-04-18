#ifndef SIGNAL_H
#define SIGNAL_H
#include "Draw.h"
#include <signal.h>
#include <sys/time.h>

void my_timer(int signo);
void my_signal(int signo);

#endif
