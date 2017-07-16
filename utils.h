#ifndef FLOWED_UTILS_H
#define FLOWED_UTILS_H


#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "global.h"


void enableRawMode();

void disableRawMode();

void writeStdout(char*, uint32_t, bool);

char getCharFromStdin();

void _getCharFromStdin(char*);

char* readStdin();

void die(char*);

void flush();

void _refreshScreen();


#endif
