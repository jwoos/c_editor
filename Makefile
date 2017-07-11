CC = gcc
CC = gcc
WARNING = -Wall -Wextra
OPTIMIZE = -O0
DEBUG = -ggdb
STD = -std=gnu11
ARGS = $(WARNING) $(OPTIMIZE) $(DEBUG) $(STD)

ALL = utils.o
EXECUTABLES = tester flowed

default: clean flowed

test: clean tester

debug: default
	valgrind --leak-check=full -v ./flowed

flowed: $(ALL)
	$(CC) $(ARGS) $@.c $^ -o $@

tester: ${ALL}
	${CC} ${ARGS} $@.c $^ -o $@

%.o: %.cpp
	${CXX} ${ARGS} -c $^ -o $@

clean: .FORCE force
	rm ${ALL} ${EXECUTABLES}

force:
	touch ${ALL} ${EXECUTABLES}

.FORCE:
