#include <ctype.h>

#include "editor.h"
#include "macros.h"
#include "utils.h"


int main() {
	enableRawMode();
	initialize();

	while (true) {
		refreshScreen();
		char c = getCharFromStdin();
		processKeyPress(c);
	}

	return EXIT_SUCCESS;
}
