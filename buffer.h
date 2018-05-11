#ifndef FLOWED_BUFFER_H
#define FLOWED_BUFFER_H


#include <string.h>
#include <stdlib.h>

#include "utils.h"


typedef struct Buffer {
	char** lines;
	uint64_t size;
};


Buffer* bufferConstruct(uint64_t);

void bufferDeconstruct(Buffer*);


#endif
