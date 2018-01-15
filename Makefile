CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -ggdb -O0
LDLIBS = -ltermbox
LDFLAGS =

OBJECTS = buffer.o editor.o utils.o
EXECUTABLES = flowed

default: clean flowed

# implicit rule for %.o
# $(CC) $(CPPFLAGS) $(CFLAGS) -c $@

flowed: ${OBJECTS}
	$(CC) flowed.c $^ $(LDFLAGS) $(LDLIBS) -o $@

objects: ${OBJECTS}

clean-objects:
	touch ${OBJECTS} && rm ${OBJECTS}

clean-executables:
	touch ${EXECUTABLES} && rm ${EXECUTABLES}

clean: clean-objects clean-executables
