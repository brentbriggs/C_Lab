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
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024
#define MAX_LINE_LENGTH 128

#define MODE_READ_BEGINNING "r" /* file must exist */
#define MODE_READ_WRITE_BEGINNING "r+" /* file must exist */
#define MODE_WRITE_TRUNCATE "w"
#define MODE_READ_WRITE_TRUNCATE "w+"
#define MODE_APPEND_WRITE "a"
#define MODE_APPEND_READ_WRITE "a+"

typedef struct file_s {
    char *pathname;
    FILE *file_p;
} file_s;

/** Constructors */
file_s *file_new(char *pathname, char *mode);

/** Destructors */
int file_free(file_s *file);

/** Operational functions */
int file_clear(file_s *file);
int file_compare(file_s *file1, file_s *file2);
int file_copy(file_s *file1, file_s *file2);
char ** file_get_lines(file_s *file, int start, int count);
int file_line_count(file_s *file);
int file_print(file_s *file);
int file_put_line(file_s *file, char *string);
