SHELL=/bin/zsh
CC = clang
CFLAGS = `pkg-config --cflags glib-2.0` -g -Wall -O0 -std=c11 -x c
DEPS = fileio.h
LDLIBS = `pkg-config --clibs glib-2.0`
OBJECTS = fileio.o fileio_test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

fileio_test : $(OBJECTS)
	$(CC)  $(LDLIBS) -o $@ $^

.PHONY : clean
clean :
	rm -rf $(OBJECTS) *(x)
