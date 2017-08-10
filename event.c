#include "event.h"


void parseEvent(struct tb_event event) {
	switch (event.type) {
		case TB_EVENT_KEY:
			onKey(event);
			break;

		case TB_EVENT_RESIZE:
			onResize(event);
			break;

		case TB_EVENT_MOUSE:
			onMouse(event);
			break;
	}
}

void onKey(struct tb_event event) {
	if (event.ch) {
		showLetter(event.ch);
	} else {

	}
}

void onResize(struct tb_event event) {

}

void onMouse(struct tb_event event) {

}
