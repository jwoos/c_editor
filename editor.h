#ifndef FLOWED_EDITOR_H
#define FLOWED_EDITOR_H


#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "buffer.h"
#include "global.h"
#include "macros.h"
#include "utils.h"


enum editorKey {
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  DEL_KEY,
  HOME_KEY,
  END_KEY,
  PAGE_UP,
  PAGE_DOWN
};

void processKeyPress(int);

void refreshScreen();

void drawRows(AppendBuffer*);

void initialize();

void moveCursor(int);

int readKey();


#endif
