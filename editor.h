#ifndef FLOWED_EDITOR_H
#define FLOWED_EDITOR_H


#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "global.h"
#include "macros.h"
#include "utils.h"


void processKeyPress(char);

void refreshScreen();

void drawRows();

void initialize();


#endif
