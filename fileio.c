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
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h> /* sys/file.h of BSD unicies, fcntl.h for Sys V */
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

int main() {
    /* File IO using stdio.h */
    char *filename1 = "test_file1.txt";
    char *filename2 = "test_file2.txt";

    /* Write to file. */
    char *test_line = "This is a test line.";
    printf("Writing to file1: %s\n", test_line);
    file_put_line(filename1, test_line);
    printf("file1:\n");
    file_print(filename1);

    /* Copy the file */
    printf("Copying file1 to file2.\n");
    file_copy(filename1, filename2);
    printf("file2:\n");
    file_print(filename2);

    /* Compare the files */
    int ln_num = 0;
    if((ln_num = file_compare(filename1, filename2)) != 0) {
        printf ("Files are different at line %-3i\n", ln_num);
    }
    else {
        printf("The files are the same.\n");
    }
    printf("file1:\n");
    file_print(filename1);
    printf("file2:\n");
    file_print(filename2);

    /* Append text to file2 */
    test_line = "Appended text.";
    printf("\n");
    printf("Append text to file2: %s\n", test_line);
    file_put_line(filename2, test_line);
    ln_num = 0;
    if((ln_num = file_compare(filename1, filename2)) != 0) {
        printf ("Files are different at line %-3i\n", ln_num);
    }
    else {
        printf("The files are the same.\n");
    }
    printf("file1:\n");
    file_print(filename1);
    printf("file2:\n");
    file_print(filename2);

    /* Count the number of lines in a file. */
    printf("%s Line Count: %3i\n", filename1, file_line_count(filename1));
    printf("%s Line Count: %3i\n", filename2, file_line_count(filename2));
    file_clear(filename1);
    file_clear(filename2);

    /* test correct line count with non terminated line */
    FILE *file = fopen(filename1, "w+");
    fputs("Non terminated line", file);
    fclose(file);
    printf("%s Line Count: %3i\n", filename1, file_line_count(filename1));
    printf("file1:\n");
    file_print(filename1);
    printf("\n");


    /* Clear file contents. */
    printf("Clear the contents of both files.\n");
    file_clear(filename1);
    file_clear(filename2);
    printf("file1:\n");
    file_print(filename1);
    printf("file2:\n");
    file_print(filename2);

    /* Remove files. */
    remove(filename1);
    remove(filename2);


    /* File IO using unix system calls */
}
