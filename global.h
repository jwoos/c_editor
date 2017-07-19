#ifndef FLOWED_GLOBAL_H
#define FLOWED_GLOBAL_H


#include <termios.h>


struct Config {
	struct termios originalTermios;
	int screenRows;
	int screenCols;
	int cx;
	int cy;
} E;


#endif
