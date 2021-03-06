#ifndef MTLIB_H
#define MTLIB_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "../../Lab-1/src/MSC_lib.h"

enum colors {black, red, green, yellow, blue,
		purple, cyan, white} colors;

int mt_clrscr();
int mt_gotoXY(int x, int y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors);
int mt_setbgcolor(enum colors);

void CONSOLE_TEST();

#endif