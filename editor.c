#include "editor.h"


void init() {
	tb_init();
	tb_select_output_mode(TB_OUTPUT_NORMAL);

	Config.cx = 0;
	Config.cy = 0;

	tb_set_cursor(Config.cx, Config.cy);

	Config.cols = tb_width();
	Config.rows = tb_height();
}

void moveCursor(uint16_t direction) {
	switch (direction) {
		case TB_KEY_ARROW_DOWN:
			if (Config.cy != Config.rows - 1) {
				Config.cy++;
			}

		case TB_KEY_ARROW_UP:
			if (Config.cy != 0) {
				Config.cy--;
			}

		case TB_KEY_ARROW_LEFT:
			if (Config.cx != 0) {
				Config.cx--;
			}

		case TB_KEY_ARROW_RIGHT:
			if (Config.cx != Config.cols - 1) {
				Config.cx++;
			}

		default:
			tb_set_cursor(Config.cx, Config.cy);
			tb_present();
	}
}

void showLetter(uint32_t ch) {
	tb_change_cell(Config.cx, Config.cy, ch, TB_DEFAULT, TB_DEFAULT);
	Config.cx++;
	tb_set_cursor(Config.cx, Config.cy);
	tb_present();
}
