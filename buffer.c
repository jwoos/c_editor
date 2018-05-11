#include "buffer.h"


Buffer* bufferConstruct(uint64_t size) {
	Buffer* buf = malloc(sizeof(*buf));
	if (buf == NULL) {
		die("malloc");
	}

	if (!size) {
		size = DEFAULT_BUFFER_SIZE;
	}

	buf -> size = size;

	buf -> lines = calloc(buf -> size, sizeof(char*));
	if (buf -> lines == NULL) {
		die("calloc");
	}

	for (uint64_t i = 0; i < buf -> size; i++) {
		buf -> lines[index] = calloc(DEFAULT_LINE_SIZE, sizeof(char));
		if (buf -> lines[index] == NULL) {
			die("calloc");
		}
	}

	return buf;
}

void bufferDeconstruct(Buffer* buf) {
	for (uint64_t i = 0; i < buf -> size; i++) {
		free(buf -> lines[index]);
	}
	free(buf -> lines);
	free(buf);
}

char* bufferGet(Buffer* buf, uint64_t index) {
	return buf -> lines[index];
}

void bufferSet(Buffer* buf, uint64_t index, Line* line) {
	buf -> lines[index] = line;
}

void bufferInsert(Buffer* buf, uint64_t index, Line* line) {
	buf -> size++;
	buf -> lines = realloc(buf -> size * sizeof(Line*));
	if (buf -> lines == NULL) {
		die("realloc");
	}

	buf -> lines[index] = line;
}

void bufferDelete(Buffer* buf, uint64_t index) {
	free(buf -> lines[index]);
	memmove(buf -> lines + index, buf -> lines + index + 1, sizeof(Line*) * buf -> size - index);
}
