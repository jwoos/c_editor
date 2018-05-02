#ifndef FLOWED_EVENT_H
#define FLOWED_EVENT_H


#include "vendor/termbox/termbox.h"

#include "global.h"
#include "utils.h"


void parseEvent(struct tb_event event);

void onKey(struct tb_event);

void onResize(struct tb_event);

void onMouse(struct tb_event);


#endif
