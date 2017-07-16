CC = gcc
WARNING = -Wall -Wextra
OPTIMIZE = -O0
DEBUG = -ggdb
STD = -std=gnu11
ARGS = $(WARNING) $(OPTIMIZE) $(DEBUG) $(STD)

ALL = utils.o editor.o
EXECUTABLES = tester flowed

ifneq ($(RELEASE), 1)
DEBUG = -ggdb
OPTIMIZE = -O0
ALL += debug-utils.o
else
OPTIMIZE = -O5
DEBUG = -g0
endif

default: clean flowed

test: clean tester

mem-check:
	valgrind --leak-check=full -v ./flowed

flowed: $(ALL)
	$(CC) $(ARGS) $@.c $^ -o $@

tester: $(ALL)
	$(CC) $(ARGS) $@.c $^ -o $@

%.o: %.cpp
	$(CXX) $(ARGS) -c $^ -o $@

clean: .PHONY force
	rm $(ALL) $(EXECUTABLES)

force:
	touch $(ALL) $(EXECUTABLES)

.PHONY:
