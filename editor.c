#include "editor.h"

void processKeyPress(int c) {
	switch (c) {
		case CTRL_KEY('q'):
			writeStdout("\x1b[2J", 4, false);
			writeStdout("\x1b[H", 3, false);
			exit(EXIT_SUCCESS);
			break;

		case HOME_KEY:
			E.cx = 0;
			break;

		case END_KEY:
			E.cx = E.screenCols - 1;
			break;

		case PAGE_UP:
		case PAGE_DOWN: {
			int times = E.screenRows;
			while (times--) {
				moveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
			}
			break;
		}

		case ARROW_RIGHT:
		case ARROW_DOWN:
		case ARROW_UP:
		case ARROW_LEFT:
			moveCursor(c);
			break;
	}
}

void refreshScreen() {
	AppendBuffer ab = ABUF_INIT;

	abAppend(&ab, "\x1b[?25l", 6);
	abAppend(&ab, "\x1b[h", 3);

	drawRows(&ab);

	char buf[32];
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy + 1, E.cx + 1);
	abAppend(&ab, buf, strlen(buf));

	abAppend(&ab, "\x1b[?25h", 6);

	writeStdout(ab.b, ab.len, false);
	abFree(&ab);
}

void drawRows(AppendBuffer* ab) {
	for (int y = 0; y < E.screenRows; y++) {
		if (y == E.screenRows / 3) {
			char welcome[80];
			int welcomeLen = snprintf(
				welcome,
				sizeof(welcome),
				"Flowed -- version %s",
				FLOWED_VERSION
			);

			if (welcomeLen > E.screenCols) {
				welcomeLen = E.screenCols;
			}

			int padding = (E.screenCols - welcomeLen) / 2;
			if (padding) {
				abAppend(ab, "~", 1);
				padding--;
			}

			while (padding--) {
				abAppend(ab, " ", 1);
			}

			abAppend(ab, welcome, welcomeLen);
		} else {
			abAppend(ab, "~", 1);
		}

		abAppend(ab, "\x1b[K", 3);
		if (y < E.screenRows - 1) {
			abAppend(ab, "\r\n", 2);
		}
	}
}

void initialize() {
	E.cx = 0;
	E.cy = 0;

	if (getWindowSize(&E.screenRows, &E.screenCols) == -1) {
		die("getWindowSize");
	}
}

void moveCursor(int key) {
	switch (key) {
		case ARROW_LEFT:
			if (E.cx != 0) {
				E.cx--;
			}
			break;
		case ARROW_RIGHT:
			if (E.cx != E.screenCols - 1) {
				E.cx++;
			}
			break;
		case ARROW_UP:
			if (E.cy != 0) {
				E.cy++;
			}
			break;
		case ARROW_DOWN:
			if (E.cy != E.screenRows - 1) {
				E.cy--;
			}
			break;
	}
}

int readKey() {
	int nread;
	char c;

	while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
		if (nread == -1 && errno != EAGAIN) {
			die("read");
		}
	}

	if (c == '\x1b') {
		char seq[3];

		if (read(STDIN_FILENO, &seq[0], 1) != 1) {
			return '\x1b';
		}

		if (read(STDIN_FILENO, &seq[1], 1) != 1) {
			return '\x1b';
		}

		if (seq[0] == '[') {
			if (seq[1] >= '0' && seq[1] <= '9') {
				if (read(STDIN_FILENO, &seq[2], 1) != 1) {
					return '\x1b';
				}

				if (seq[2] == '~') {
					switch (seq[1]) {
						case '1':
							return HOME_KEY;

						case '3':
							return DEL_KEY;

						case '4':
							return END_KEY;

						case '5':
							return PAGE_UP;

						case '6':
							return PAGE_DOWN;

						case '7':
							return HOME_KEY;

						case '8':
							return END_KEY;
					}
				}
			} else {
				switch (seq[1]) {
					case 'A':
						return ARROW_UP;

					case 'B':
						return ARROW_DOWN;

					case 'C':
						return ARROW_RIGHT;

					case 'D':
						return ARROW_RIGHT;

					case 'H':
						return HOME_KEY;

					case 'F':
						return END_KEY;
				}
			}
		} else if (seq[0] == 'O') {
			switch (seq[1]) {
				case 'H':
					return HOME_KEY;

				case 'F':
					return END_KEY;
			}
		}

		return '\x1b';
	} else {
		return c;
	}
}
