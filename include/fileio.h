/******************************************************************************
 * Author: Brent Briggs
 * Date: 2014-02-08 14:43:09
 *
 * LICENSE:
 * This software is released under the WTF Puplic License as described at
 * www.wtfpl.net. So do WTF you want.
 *
 * DESCRIPTION:
 * Header file for fileio.c. Defines functions related to file io using the C
 * standard library as well as unix system calls.
 *****************************************************************************/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h> /* sys/file.h if BSD unicies, fcntl.h for Sys V */
#include <unistd.h>

#define BUFSIZE 1024
#define MAX_LINE_LENGTH 120

int file_clear(char *filepath);
int file_close(FILE *file);
int file_compare(char *filepath1, char *filepath2);
int file_copy(char *filepath1, char *filepath2);
int file_line_count(char *filepath);
FILE *file_open(char *filepath, char *mode);
int file_print(char *filepath);
int file_put_line(char *filepath, char *string);
