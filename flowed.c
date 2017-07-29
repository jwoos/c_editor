#include <termbox.h>

#include "global.h"
#include "utils.h"


int main() {
	tb_init();
	tb_select_output_mode(TB_OUTPUT_NORMAL);

	tb_set_cursor(0, 0);

	struct tb_event event;
	tb_poll_event(&event);

	tb_shutdown();

	return EXIT_SUCCESS;
}
