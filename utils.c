#include "utils.h"


void enableRawMode() {
	tcgetattr(STDIN_FILENO, &originalTermios);
	atexit(disableRawMode);

	struct termios raw = originalTermios;

	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTermios);
}

void writeStdout(char* message, uint32_t bytes) {
	if (write(STDOUT_FILENO, message, bytes) < 0) {
		printError("error writing - exiting", 1);
	}
}

char getCharFromStdin() {
	char buffer;

	_getCharFromStdin(&buffer);

	return buffer;
}

void _getCharFromStdin(char* pc) {
	char c = *pc;
	int bytesRead = read(STDIN_FILENO, pc, 1);

	if (bytesRead < 0) {
		printError("error reading - exiting", true);
	} else if (bytesRead == 0) {
		c = '\0';
	}
}

char* readStdin() {
	uint32_t original = 256;
	uint32_t size = 256;
	uint32_t position = 0;
	char* buffer = calloc(size, sizeof(char));
	char c;

	if (!buffer) {
		printError("Error allocating", 1);
	}

	while (1) {
		c = getCharFromStdin();

		if (c == '\0' && position == 0) {
			_exit(EXIT_SUCCESS);
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
				printError("Error allocating", true);
			}
		}
	}

	return buffer;
}

void printError(char* message, bool shouldExit) {
	perror(message);

	if (shouldExit) {
		_exit(EXIT_FAILURE);
	}
}

void flush() {
	writeStdout("\n", 1);
}
