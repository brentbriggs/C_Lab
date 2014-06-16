SHELL=/bin/zsh
TARGETDIR := ./bin
SRCDIR := ./src
OBJECTS =
CFLAGS = `pkg-config --cflags glib-2.0 gsl` -g -Wall -O0 -std=c11 -x c
LDLIBS = `pkg-config --libs glib-2.0 gsl`
CC = clang

.PHONY : all
all : file_io

file_io : $(TARGETDIR)/file_io
.DELETE_ON_ERROR : $(TARGETDIR)/file_io
$(TARGETDIR)/file_io : $(SRCDIR)/file_io.c $(OBJECTS) | $(TARGETDIR)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

$(TARGETDIR) :
	mkdir $(TARGETDIR)

.PHONY : clean
clean :
	rm -rf $(TARGETDIR)/*
