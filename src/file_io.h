/******************************************************************************
 * Author: Brent Briggs
 * Date: 2014-02-08 14:43:09
 *
 * LICENSE:
 * This software is released under the WTF Puplic License as described at
 * www.wtfpl.net. So do WTF you want.
 *
 * DESCRIPTION:
 * Definition for "file" object and functions.
 *****************************************************************************/
#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024
#define MAX_LINE_LENGTH 128

#define MODE_READ_BEGINNING "r" /* file must exist */
#define MODE_READ_WRITE_BEGINNING "r+" /* file must exist */
#define MODE_WRITE_TRUNCATE "w" /* Creates empty file for writing or erases
                                   contents of */
#define MODE_READ_WRITE_TRUNCATE "w+"
#define MODE_APPEND_WRITE "a"
#define MODE_APPEND_READ_WRITE "a+"

int file_clear(char *filename);
int file_close(FILE *file);
int file_compare(char *filename1, char *filename2);
int file_copy(char *file1, char *file2);
char ** file_get_lines(char *filename, int start, int count);
int file_line_count(char *filename);
FILE *file_open(char *filename, char *mode);
int file_print(char *filename);
int file_put_line(char *filename, char *string);
int file_remove(char *filename);
