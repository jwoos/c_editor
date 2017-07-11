#include "utils.h"


int main() {
	enableRawMode();

	char c;
	while (true) {
		_getCharFromStdin(&c);

		if (c == 'q') {
			break;
		}
	}

	return 0;
}
