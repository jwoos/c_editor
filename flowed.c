#include <stdio.h>
#include <termbox.h>

#include "editor.h"
#include "global.h"
#include "utils.h"


int main() {
	init();

	tb_present();

	struct tb_event event;
	int status;
	while (status >= 0) {
		status = tb_poll_event(&event);

		if (event.ch) {
			showLetter(event.ch);
		} else {
			switch (event.key) {
				case TB_KEY_CTRL_Q:
					status = -1;
					break;

				case TB_KEY_ARROW_UP:
				case TB_KEY_ARROW_DOWN:
				case TB_KEY_ARROW_LEFT:
				case TB_KEY_ARROW_RIGHT:
					moveCursor(event.key);
					break;
			}
		}
	};

	tb_shutdown();

	printf("%d\n", Config.cx);
	printf("%d\n", Config.cy);

	return EXIT_SUCCESS;
}
