CC = gcc
WARNINGS_ERRORS = -Wall
STANDARD = -std=gnu11
OPTIMIZE = -O0
DEBUG = -ggdb
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

CFLAGS = $(WARNINGS_ERRORS) $(STANDARD) $(DEBUG) $(OPTIMIZE)


default: clean flowed

mem-check:
	valgrind --leak-check=full -v ./flowed

flowed: $(ALL)

clean: .PHONY force
	rm $(ALL) $(EXECUTABLES)

force:
	touch $(ALL) $(EXECUTABLES)

.PHONY:
