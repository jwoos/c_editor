#ifndef FLOWED_GLOBAL_H
#define FLOWED_GLOBAL_H


#define FLOWED_VERSION "0.0.1"

#define CTRL_KEY(k) ((k) & 0x1f)
#define ABUF_INIT {NULL, 0}


struct Config {
	int cols;
	int rows;
	int cx;
	int cy;
} Config;


#endif
