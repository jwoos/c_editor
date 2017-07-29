CC = gcc
CFLAGS = -Wall -std=gnu11 -ggdb -O0
LDLIBS = -ltermbox

ALL = utils.o editor.o buffer.o
EXECUTABLES = flowed

ifneq ($(RELEASE), 1)
DEBUG = -ggdb
OPTIMIZE = -O0
else
OPTIMIZE = -O5
DEBUG = -g0
endif

default: clean flowed

mem-check:
	valgrind --leak-check=full -v ./flowed

flowed: $(ALL)

clean: .PHONY force
	rm $(ALL) $(EXECUTABLES)

force:
	touch $(ALL) $(EXECUTABLES)

.PHONY:
