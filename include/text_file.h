/******************************************************************************
 * Author: Brent Briggs
 * Date: 2014-02-08 14:43:09
 *
 * LICENSE:
 * This software is released under the WTF Puplic License as described at
 * www.wtfpl.net. So do WTF you want.
 *
 * DESCRIPTION:
 * Definition for "text_file_s" structure and related functions.
 *****************************************************************************/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024
#define MAX_LINE_LENGTH 128
#define MODE_READ_BEGINNING "r"
#define MODE_READ_WRITE_BEGINNING "r+"


typedef struct text_file_s {
    char *filename;
    FILE *file_p;
} text_file_s;

/** Constructors */
text_file_s *text_file_new(char *pathname, char *mode);

/** Destructors */
int text_file_free(text_file_s *file);

/** Operational functions */
int text_file_set_mode(text_file_s *file, char *mode);
int text_file_append_line(text_file_s *file, char *string);
int text_file_clear(text_file_s *file);
int text_file_compare(text_file_s *file1, text_file_s *file2);
int text_file_copy(text_file_s *file1, text_file_s *file2);
char ** text_file_get_lines(text_file_s *file, int start, int count);
int text_file_line_count(text_file_s *file);
int text_file_print(text_file_s *file);
int text_file_put_line(text_file_s *file, char *string);
