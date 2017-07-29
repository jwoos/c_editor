#include "utils.h"


int writeStdout(char* message, uint32_t bytes, bool newLine) {
	if (newLine) {
		bytes += 2;
		char buffer[bytes];

		strcat(buffer, message);
		strcat(buffer, "\r\n");
		message = buffer;
	}

	int written = write(STDOUT_FILENO, message, bytes);

	if (written < 0) {
		die("write");
	}

	return written;
}

char getCharFromStdin() {
	char buffer;

	_getCharFromStdin(&buffer);

	return buffer;
}

void _getCharFromStdin(char* pc) {
	char c = *pc;
	int bytesRead = read(STDIN_FILENO, pc, 1);

	if (bytesRead == -1 && errno != EAGAIN) {
		die("read");
	}
}

char* readStdin() {
	uint32_t original = 256;
	uint32_t size = 256;
	uint32_t position = 0;
	char* buffer = calloc(size, sizeof(char));
	char c;

	if (!buffer) {
		die("calloc");
	}

	while (1) {
		c = getCharFromStdin();

		if (c == '\0' && position == 0) {
			exit(EXIT_SUCCESS);
		} if (c == '\n') {
			buffer[position] = '\0';
			break;
		}

		buffer[position] = c;
		position++;

		if (position >= size) {
			size += original;
			buffer = realloc(buffer, size);

			if (!buffer) {
				die("realloc");
			}
		}
	}

	return buffer;
}

void die(char* message) {
	perror(message);
	exit(EXIT_FAILURE);
}
