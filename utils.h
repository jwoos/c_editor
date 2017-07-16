#ifndef FLOWED_UTILS_H
#define FLOWED_UTILS_H

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>


struct termios originalTermios;

void enableRawMode();

void disableRawMode();

void writeStdout(char*, uint32_t);

char getCharFromStdin();

void _getCharFromStdin(char*);

char* readStdin();

void printError(char*, bool);

void flush();

void refreshScreen();


#endif
