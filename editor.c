#include "editor.h"

void processKeyPress(char c) {
	switch (c) {
		case CTRL_KEY('q'):
			exit(EXIT_SUCCESS);
	}
}

void refreshScreen() {
	_refreshScreen();

	drawRows();
	writeStdout("\x1b[H", 3, false);
}

void drawRows() {
	for (int y = 0; y < 24; y++) {
		writeStdout("~", 1, true);
	}
}
