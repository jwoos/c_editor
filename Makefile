CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -ggdb -O0
LDLIBS = termbox.a
LDFLAGS = -L.
LIBS = termbox.a

OBJECTS = buffer.o editor.o utils.o termbox.a
EXECUTABLES = flowed

default: clean flowed

# implicit rule for %.o
# $(CC) $(CPPFLAGS) $(CFLAGS) -c $@

flowed: ${OBJECTS}
	$(CC) flowed.c $^ $(LDFLAGS) $(LDLIBS) -o $@

objects: ${OBJECTS}

termbox.a: vendor/termbox/termbox.o vendor/termbox/utf8.o
	ar -rcs $@ $^

clean-objects:
	touch ${OBJECTS} && rm ${OBJECTS}

clean-executables:
	touch ${EXECUTABLES} && rm ${EXECUTABLES}

clean: clean-objects clean-executables
