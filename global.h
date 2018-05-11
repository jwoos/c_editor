#ifndef FLOWED_GLOBAL_H
#define FLOWED_GLOBAL_H


#include <stdbool.h>

#include "vendor/termbox/termbox.h"


#define CTRL_KEY(k) ((k) & 0x1f)
#define ABUF_INIT {NULL, 0}

#define DEFAULT_INCREASE_FACTOR 2
#define DEFAULT_BUFFER_SIZE 32
#define DEFAULT_LINE_SIZE 64


struct Config {
	// for scrolling
	uint64_t offset;

	// terminal dimensions
	uint64_t cols;
	uint64_t rows;

	// cursor location
	uint64_t cx;
	uint64_t cy;

	// current lines
	uint64_t lines;

	bool modified;

	tb_cell* buffer;
} Config;


#endif
