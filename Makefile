SHELL=/bin/zsh
TARGETDIR := ./bin
SRCDIR := src
OBJECTS =
CFLAGS = -L/Users/brent/dev/lib `pkg-config --cflags glib-2.0 gsl` -g -Wall -O0 -std=c11 -x c
LDLIBS = -I/Users/brent/dev/include `pkg-config --libs glib-2.0 gsl`
CC = clang

all : $(TARGETDIR)/fileio

.DELETE_ON_ERROR : $(TARGETDIR)/fileio
$(TARGETDIR)/fileio : fileio.c $(OBJECTS) | $(TARGETDIR)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

$(TARGETDIR) :
	mkdir $(TARGETDIR)

.PHONY : clean
clean :
	rm -rf $(OBJECTS) $(TARGETDIR)/*.dSYM $(TARGETDIR)/*(x) $(TARGETDIR)/*.[^c*]*
