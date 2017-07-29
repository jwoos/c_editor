#include <ctype.h>
#include <termbox.h>

#include "editor.h"
#include "macros.h"
#include "utils.h"


int main() {
	tb_init();
	tb_shutdown();

	return EXIT_SUCCESS;
}
