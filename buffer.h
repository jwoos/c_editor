#ifndef FLOWED_BUFFER_H
#define FLOWED_BUFFER_H


#include <string.h>
#include <stdlib.h>


typedef struct AppendBuffer {
	char* b;
	int len;
} AppendBuffer;

void abAppend(AppendBuffer*, const char*, int);

void abFree(AppendBuffer*);


#endif
