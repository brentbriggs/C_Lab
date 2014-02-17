/******************************************************************************
 * Author: Brent Briggs
 * Date: 2014-01-24 15:59:09
 *
 * LICENSE:
 * This software is released under the WTF Puplic License as described at
 * www.wtfpl.net. So do WTF you want.
 *
 * DESCRIPTION:
 * Collection of example C code for handling file IO.
 *****************************************************************************/
#include "fileio.h"

int file_clear(char *filepath) {
    FILE *file = file_open(filepath, "w");
    file_close(file);
    return 0;
}

int file_close(FILE *file) {
    if (fclose(file) != EOF) {
        return 0;
    }
    else {
        fprintf(stderr, "Error: Could not close file\n");
        return 1;
    }
}

/* Compare text files line by line. */
int file_compare(char *filepath1, char *filepath2) {
    FILE *file1 = file_open(filepath1, "r");
    FILE *file2 = file_open(filepath2, "r");
    char file1_line[MAX_LINE_LENGTH];
    char file2_line[MAX_LINE_LENGTH];

    int line_count = 0;

    while((fgets(file1_line, MAX_LINE_LENGTH, file1)) &&
            (fgets(file2_line, MAX_LINE_LENGTH, file2))) {
        ++line_count;
        if(strcmp(file1_line, file2_line) != 0 ) {
            return line_count;
        }
    }
    if((fgets(file1_line, MAX_LINE_LENGTH, file1)) ||
            (fgets(file2_line, MAX_LINE_LENGTH, file2))) {
        return ++line_count;
    }
    return 0;
}

int file_copy(char *filepath1, char *filepath2) {
    FILE *file1 = file_open(filepath1, "r");
    FILE *file2 = file_open(filepath2, "w+");
    int c;
    while((c = fgetc(file1)) != EOF) {
        fputc(c, file2);
    }
    file_close(file1);
    file_close(file2);
    return 0;
}

int file_line_count(char *filepath) {
    FILE *file = file_open(filepath, "r");
    int line_count = 0;
    char line[MAX_LINE_LENGTH];

    while(fgets(line, MAX_LINE_LENGTH, file)) {
            line_count++;
    }
    file_close(file);
    return line_count;
}

FILE *file_open(char *filepath, char *mode) {
    FILE *fp = NULL;
    if(!(fp = fopen(filepath, mode))) {
        fprintf(stderr, "Error: Could not open file %s\n", filepath);
    }
    return fp;
}

int file_print(char *filepath) {
    FILE *file = file_open(filepath, "r");
    int c;
    while((c = fgetc(file)) != EOF) {
        fputc(c, stdout);
    }
    file_close(file);
    return 0;
}

int file_put_line(char *filepath, char *string) {
    int status = 0;
    FILE *file = file_open(filepath, "a");
    if(file != NULL) {
        fputs(string, file);
        fputs("\n", file);
    }
    if((file_close(file)) != 0) {
        status = 1;
    }
    return status;
}


