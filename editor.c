#include "editor.h"

void processKeyPress(char c) {
	switch (c) {
		case CTRL_KEY('q'):
			exit(EXIT_SUCCESS);
	}
}
