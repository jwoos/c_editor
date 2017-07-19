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

// TODO
void concatArr(void* dest, void* addon) {}

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
	_refreshScreen();

	perror(message);
	exit(EXIT_FAILURE);
}

void _refreshScreen() {
	writeStdout("\x1b[2J", 4, false);
	writeStdout("\x1b[H", 3, false);
}

int getCursorPosition(int* rows, int* cols) {
	char buf[32];
	uint32_t i = 0;

	if (writeStdout("\x1b[6n", 4, false) != 4) {
		return -1;
	}

	while (i < sizeof(buf) - 1) {
		if (read(STDIN_FILENO, &buf[i], 1) != 1) {
			break;
		}

		if (buf[i] == 'R') {
			break;
		}

		i++;
	}
	buf[i] = '\0';

	if (buf[0] != '\x1b' || buf[1] != '[') {
		return -1;
	}

	if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) {
		return -1;
	}

	return 0;
}

int getWindowSize(int* rows, int* cols) {
	struct winsize ws;

	int status = 0;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
		if (writeStdout("\x1b[999C\x1b[999B", 12, false) == 12) {
			status = getCursorPosition(rows, cols);
		}
		status = -1;
	} else {
		*cols = ws.ws_col;
		*rows = ws.ws_row;
	}

	return status;
}
