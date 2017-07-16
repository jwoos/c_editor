#include "utils.h"


void enableRawMode() {
	if (tcgetattr(STDIN_FILENO, &E.originalTermios) == -1) {
		die("tcgetattr");
	}

	atexit(disableRawMode);

	struct termios raw = E.originalTermios;

	/* ECHO disables echoing
	 * ICANON allows consuming byte by byte
	 * ISIG disables ctrl-c and ctrl-z
	 * IXON disables ctrl-s and ctrl-q
	 * IEXTEN disables ctrl-v literal sending
	 * ICRNL fixes ctrl-m
	 * OPOST fixes the newline translation for output
	 */
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

	// set read timeout
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
		die("tcsetattr");
	}
}

void disableRawMode() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.originalTermios) == -1) {
		die("tcsetattr");
	}
}

void writeStdout(char* message, uint32_t bytes, bool newLine) {
	if (newLine) {
		char buffer[bytes + 2];

		strcat(buffer, message);
		strcat(buffer, "\r\n");
		message = buffer;
	}

	if (write(STDOUT_FILENO, message, bytes) < 0) {
		die("write");
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
	_refreshScreen();

	perror(message);
	exit(EXIT_FAILURE);
}

void _refreshScreen() {
	writeStdout("\x1b[2J", 4, false);
	writeStdout("\x1b[H", 3, false);
}
