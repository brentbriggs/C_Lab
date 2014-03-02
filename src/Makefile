INC_DIR=../include
LDIR=../lib
OBJ_DIR=obj
SHELL=/bin/zsh
_DEPS=text_file.h
DEPS=$(patsubst %,$(INC_DIR)/%,$(_DEPS))

_OBJ=text_file.o text_file_test.o
OBJ=$(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

CFLAGS=-I$(INC_DIR) `pkg-config --cflags glib-2.0` -g -Wall -O0 -std=c11 -x c
LDLIBS=`pkg-config --libs glib-2.0`
CC=clang

$(OBJ_DIR)/%.o: %.c $(DEPS) | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

text_file_test : $(OBJ)
	$(CC) $(LDLIBS) -o $@ $^

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY : clean
clean :
	rm -rf $(OBJ_DIR)/*.o *(x)
