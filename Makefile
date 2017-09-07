SHELL=/bin/zsh
TARGETDIR := ./bin
SRCDIR := ./src
OBJECTS =
CFLAGS = `pkg-config --cflags glib-2.0 gsl` -g -Wall -O0 -std=gnu11 -x c
LDLIBS = `pkg-config --libs glib-2.0 gsl`
CC = clang

.PHONY : all
all : file_io garray_demo ghashtable_demo glist_demo gslist_demo gtree_demo \
	  gqueue_demo

file_io : $(TARGETDIR)/file_io
.DELETE_ON_ERROR : $(TARGETDIR)/file_io
$(TARGETDIR)/file_io : $(SRCDIR)/file_io.c $(OBJECTS) | $(TARGETDIR)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

garray_demo : $(TARGETDIR)/garray_demo
.DELETE_ON_ERROR : $(TARGETDIR)/garray_demo
$(TARGETDIR)/garray_demo : $(SRCDIR)/garray_demo.c $(OBJECTS) | $(TARGETDIR)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

ghashtable_demo : $(TARGETDIR)/ghashtable_demo
.DELETE_ON_ERROR : $(TARGETDIR)/ghashtable_demo
$(TARGETDIR)/ghashtable_demo : $(SRCDIR)/ghashtable_demo.c $(OBJECTS) | $(TARGETDIR)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

glist_demo : $(TARGETDIR)/glist_demo
.DELETE_ON_ERROR : $(TARGETDIR)/glist_demo
$(TARGETDIR)/glist_demo : $(SRCDIR)/glist_demo.c $(OBJECTS) | $(TARGETDIR)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

gslist_demo : $(TARGETDIR)/gslist_demo
.DELETE_ON_ERROR : $(TARGETDIR)/gslist_demo
$(TARGETDIR)/gslist_demo : $(SRCDIR)/gslist_demo.c $(OBJECTS) | $(TARGETDIR)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

gtree_demo : $(TARGETDIR)/gtree_demo
.DELETE_ON_ERROR : $(TARGETDIR)/gtree_demo
$(TARGETDIR)/gtree_demo : $(SRCDIR)/gtree_demo.c $(OBJECTS) | $(TARGETDIR)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

gqueue_demo : $(TARGETDIR)/gqueue_demo
.DELETE_ON_ERROR : $(TARGETDIR)/gqueue_demo
$(TARGETDIR)/gqueue_demo : $(SRCDIR)/gqueue_demo.c $(OBJECTS) | $(TARGETDIR)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@


$(TARGETDIR) :
	mkdir $(TARGETDIR)

.PHONY : clean
clean :
	rm -rf $(TARGETDIR)*
