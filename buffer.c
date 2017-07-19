#include "buffer.h"


void abAppend(AppendBuffer* ab, const char* s, int len) {
	char* new = realloc(ab -> b, ab -> len + len);

	if (new == NULL) {
		return;
	}

	memcpy(&new[ab -> len], s, len);
	ab -> b = new;
	ab -> len += len;
}

void abFree(AppendBuffer* ab) {
	free(ab -> b);
}
