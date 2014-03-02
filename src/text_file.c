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
#include "text_file.h"

/** Create a new text_file_s struct */
text_file_s *text_file_new(char *filename, char *mode) {
    text_file_s *file = malloc(sizeof(text_file_s));
    *file = (text_file_s) {.filename = filename, .file_p = NULL};
    file->file_p = fopen(filename, mode);
    if(file->file_p == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return NULL;
    }
    return file;
}

/** Free a text_file_s struct */
int text_file_free(text_file_s *file) {
    if(fclose(file->file_p) == EOF) {
        fprintf(stderr,
                "Error: Could not close opened file %s",
                file->filename);
       return 1;
    }
    free(file);
    return 0;
}

/** Clear the contents of a text file but do not delete it. */
int text_file_clear(text_file_s *file) {
    if (file->file_p != NULL)
    if(freopen(file->filename, "w", file->file_p) == NULL)
        return 1;
    return 0;
}

/** Compare text files line by line. Return the line number where they differ, 0
 * if they are the same, -1 for error. */
int text_file_compare_text(text_file_s *file1, text_file_s *file2) {
    char file1_line[MAX_LINE_LENGTH];
    char file2_line[MAX_LINE_LENGTH];

    int line_count = 0;

    while((fgets(file1_line, MAX_LINE_LENGTH, file1->file_p)) &&
            (fgets(file2_line, MAX_LINE_LENGTH, file2->file_p))) {
        ++line_count;
        if(strcmp(file1_line, file2_line) != 0 ) {
            return line_count;
        }
    }
    if((fgets(file1_line, MAX_LINE_LENGTH, file1->file_p)) ||
            (fgets(file2_line, MAX_LINE_LENGTH, file2->file_p))) {
        return ++line_count;
    }
    return 0;
}

/** copy the contents of file1 to file2 */
int text_file_copy(text_file_s *file1, text_file_s *file2) {
    int c;
    while((c = fgetc(file1->file_p)) != EOF) {
        fputc(c, file2->file_p);
    }
    if(fflush(file1->file_p) == fflush(file2->file_p) == 0)
        return 0;
    else {
        fprintf(stderr,
                "Error: Contents of file %s could not be copied to file. %s",
                file1->filename, file2->filename);
        return 1;
    }
}

/** Return count lines of text from a file starting at start.*/
char ** text_file_get_lines(text_file_s *file, int start, int count) {
    if (text_file_line_count(file) < (start + count -1)) return NULL;

    char **lines = malloc (sizeof (char *) * count);
    for(int i=0; i < count; i++) {

    }
    return lines;
}

/** Count the number of lines in a text file */
int text_file_line_count(text_file_s *file) {
    int line_count = 0;
    char line[MAX_LINE_LENGTH];

    while(fgets(line, MAX_LINE_LENGTH, file->file_p)) {
            line_count++;
    }
    return line_count;
}

/** Print the contents of file to the screan */
int text_file_print(text_file_s *file) {
    int c;
    while((c = fgetc(file->file_p)) != EOF) {
        fputc(c, stdout);
    }
    return 0;
}

/** Append a line of text to a file */
int text_file_put_line(text_file_s *file, char *string) {
    if (fputs(string, file->file_p) && fputs("\n", file->file_p)) {
        fflush(file->file_p);
        return 0;
    }
    else
        return 1;
}


