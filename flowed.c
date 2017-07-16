#include <ctype.h>

#include "editor.h"
#include "macros.h"
#include "utils.h"


int main() {
	enableRawMode();

	while (true) {
		char c = getCharFromStdin();
		processKeyPress(c);
	}

	return EXIT_SUCCESS;
}
