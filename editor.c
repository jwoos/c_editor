#include "editor.h"

void processKeyPress(char c) {
	switch (c) {
		case CTRL_KEY('q'):
			writeStdout("\x1b[2J", 4, false);
			writeStdout("\x1b[H", 3, false);
			exit(EXIT_SUCCESS);
			break;

		case 'h':
		case 'l':
		case 'j':
		case 'k':
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

void moveCursor(char key) {
	switch (key) {
		case 'h':
			E.cx--;
			break;
		case 'l':
			E.cx++;
			break;
		case 'j':
			E.cy++;
			break;
		case 'k':
			E.cy--;
			break;
	}
}
