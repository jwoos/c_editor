#ifndef FLOWED_EDITOR_H
#define FLOWED_EDITOR_H


#include <stdbool.h>
#include <termbox.h>

#include "global.h"
#include "utils.h"


void init();

void moveCursor(uint16_t);

void showLetter(uint32_t);


#endif
