/******************************************************************************
 * Author: Brent Briggs
 * Date: 2014-01-24 15:59:09
 *
 * LICENSE:
 * This software is released under the WTF Puplic License as described at
 * www.wtfpl.net. So do WTF you want.
 *
 * DESCRIPTION:
 * Implementation for text_file_s structure manipulation functions.
 *****************************************************************************/
#include "file_io.h"

/** Clear the contents of a text file but do not delete it. */
int file_clear(char *filename) {
    FILE *file = file_open(filename, MODE_WRITE_TRUNCATE);
    if(file == NULL) {
        fprintf(stderr, "ERROR: Could not clear file %s.\n", filename);
        return 1;
    }
    file_close(file);
    return 0;
}

/** Wrapper for fclose() from stdio.h. */
int file_close(FILE *file) {
    if (fclose(file) == EOF ) {
        fprintf(stderr, "ERROR: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}

/** Compare text files line by line. Return the line number where they differ, 0
 * if they are the same, -1 for error. */
int file_compare(char *filename1, char *filename2) {
    bool diff = false;

    FILE *file1 = file_open(filename1, MODE_READ_BEGINNING);
    FILE *file2 = file_open(filename2, MODE_READ_BEGINNING);
    if((file1 == NULL) || (file2 == NULL)) {
        fprintf(stderr, "ERROR: Could not compare files %s and %s.",
                filename1, filename2);
    }
    char file1_line[MAX_LINE_LENGTH];
    char file2_line[MAX_LINE_LENGTH];

    int line_count = 0;

    while((fgets(file1_line, MAX_LINE_LENGTH, file1)) &&
            (fgets(file2_line, MAX_LINE_LENGTH, file2))) {
        ++line_count;
        if(strcmp(file1_line, file2_line) != 0 ) {
            diff = true;
            break;
        }
    }
    if((fgets(file1_line, MAX_LINE_LENGTH, file1)) ||
            (fgets(file2_line, MAX_LINE_LENGTH, file2))) {
        diff = true;
        ++line_count;
    }

    file_close(file1);
    file_close(file2);
    if(diff)
        return line_count;
    else
        return 0;
}

/** copy the contents of file1 to file2. Error recovery is the resposnibility
 * of the function user. */
int file_copy(char *filename1, char *filename2) {
    int status = 0;

    FILE *file1 = file_open(filename1, MODE_READ_BEGINNING);
    FILE *file2 = file_open(filename2, MODE_WRITE_TRUNCATE);
    if((file1 == NULL) || (file2 == NULL)) {
        fprintf(stderr, "ERROR: Could not copy file1 %s to %s.",
                filename1, filename2);
        status = 1;
    } else {
        int c;
        while((c = fgetc(file1)) != EOF) {
            fputc(c, file2);
        }
        if(!(file_close(file1) == file_close(file2) == 0)) {
            fprintf(stderr,
                    "ERROR: Could not copy file1 %s to %s.",
                    filename1, filename1);
            status = 1;
        }
    }

    file_close(file1);
    file_close(file2);
    return status;
}

/** Return "count" lines of text from a file starting at start.*/
char ** file_get_lines(char *filename, int start, int count) {
    FILE *file = file_open(filename, MODE_READ_BEGINNING);
    if(file == NULL){
        fprintf(stderr, "ERROR: Could not get lines for file %s.\n", filename);
        return NULL;
    }

    if (file_line_count(filename) < (start + count -1)) return NULL;

    char **line_array = malloc (sizeof (char *) * count);
    if (!line_array) {
        return NULL;
    }
    for(int i=0; i < count; i++) {
        line_array[i] = malloc(MAX_LINE_LENGTH + 1);
        if(!line_array[i]) {
            free(line_array);
            return NULL;
        }
    }
    char str[MAX_LINE_LENGTH];
    int len;
    for(int i=0; i < (start + count - 1); i++) {
        if(fgets(str, sizeof(str), file) == NULL) {
            if(ferror(file) != 0)
                fprintf(stderr, "ERROR: %s\n", strerror(ferror(file)));
            if(feof(file) != 0) {
                fprintf(stderr, "ERROR: Attempted to read past the end of \
                        file %s.\n", filename);
            }
        }
        if(i >= (start - 1)) {
            /* remove newline */
            len = strlen(str);
            if( str[len-1] == '\n' )
                str[len-1] = 0;
            line_array[i] = strdup(str);
        }
    }

    file_close(file);
    return line_array;
}

/** Count the number of lines in a text file */
int file_line_count(char *filename) {
    FILE *file = file_open(filename, MODE_READ_BEGINNING);
    if(file == NULL){
        fprintf(stderr,
                "ERROR: Could not get line count for file %s.\n",
                filename);
        return -1;
    }

    int line_count = 0;
    char line[MAX_LINE_LENGTH];

    while(fgets(line, MAX_LINE_LENGTH, file)) {
            line_count++;
    }

    file_close(file);
    return line_count;
}

/* Wrapper for fopen() from stdio.h. */
FILE *file_open(char *filename, char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        fprintf(stderr, "ERROR: %s\n", strerror(errno));
    }
    return file;
}

/** Print the contents of file to the screan */
int file_print(char* filename) {
    FILE *file = file_open(filename, MODE_READ_BEGINNING);
    if(file == NULL){
        fprintf(stderr, "ERROR: Could not print file %s.\n", filename);
        return 1;
    }

    int c;
    while((c = fgetc(file)) != EOF) {
        fputc(c, stdout);
    }

    file_close(file);
    return 0;
}

/** Append a line of text to a file */
int file_put_line(char* filename, char *string) {
    FILE *file = file_open(filename, MODE_APPEND_WRITE);
    if(file == NULL){
        fprintf(stderr, "ERROR: Could not put line in file %s.\n", filename);
        return 1;
    }

    if (fputs(string, file) && fputs("\n", file)) {
        fflush(file);
        file_close(file);
        return 0;
    }
    else
        file_close(file);
        return 1;
}

int main(int argc, char *argv[])
{
    char *filename1 = "test_file1.txt";
    char *filename2 = "test_file2.txt";
    file_clear(filename1);
    file_clear(filename2);
    return 0;
}