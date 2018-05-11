#ifndef FLOWED_GLOBAL_H
#define FLOWED_GLOBAL_H


#include <stdbool.h>


#define CTRL_KEY(k) ((k) & 0x1f)
#define ABUF_INIT {NULL, 0}

#define DEFAULT_INCREASE_FACTOR 2
#define DEFAULT_BUFFER_SIZE 32
#define DEFAULT_LINE_SIZE 64


struct Config {
	uint64_t cols;
	uint64_t rows;
	uint64_t cx;
	uint64_t cy;

	bool modified;
} Config;


#endif
