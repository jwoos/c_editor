#include "editor.h"


void initTermbox(void) {
	tb_init();
	tb_select_output_mode(TB_OUTPUT_NORMAL);

	Config.cx = 0;
	Config.cy = 0;

	tb_set_cursor(Config.cx, Config.cy);

	Config.cols = tb_width();
	Config.rows = tb_height();

	// register exit handler
	atexit(tb_shutdown);

	tb_present();
}

struct tb_event pollEvent(void) {
	struct tb_event event;

	if (tb_poll_event(&event) < 0) {
		die("tb_poll_event");
	}

	return event;
}

struct tb_event peekEvent(uint32_t timeout) {
	struct tb_event event;

	if (tb_peek_event(&event, timeout) < 0) {
		die("tb_peek_event");
	}

	return event;
}

void moveCursor(uint16_t direction) {
	switch (direction) {
		case TB_KEY_ARROW_UP:
			if (Config.cy != 0) {
				Config.cy--;
			}
			break;

		case TB_KEY_ARROW_LEFT:
			if (Config.cx != 0) {
				Config.cx--;
			}
			break;

		case TB_KEY_ARROW_DOWN:
			if (Config.cy != Config.rows - 1) {
				Config.cy++;
			}
			break;

		case TB_KEY_ARROW_RIGHT:
			if (Config.cx != Config.cols - 1) {
				Config.cx++;
			}
			break;
	}

	tb_set_cursor(Config.cx, Config.cy);
	tb_present();
}

void showLetter(uint32_t ch) {
	tb_change_cell(Config.cx, Config.cy, ch, TB_DEFAULT, TB_DEFAULT);
	Config.cx++;
	tb_set_cursor(Config.cx, Config.cy);
	tb_present();
}

void newLine(void) {
	Config.cx = 0;
	Config.cy++;
	tb_set_cursor(Config.cx, Config.cy);
	tb_present();
}
