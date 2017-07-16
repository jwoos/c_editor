#include <ctype.h>

#include "macros.h"
#include "utils.h"


int main() {
	enableRawMode();

	while (true) {
		char c = '\0';

		_getCharFromStdin(&c);

		if (c == 'q') {
			break;
		} else if (iscntrl(c)) {
			printf("%d\r\n", c);
		} else {
			printf("%d ('%c')\r\n", c, c);
		}
	}

	return 0;
}
