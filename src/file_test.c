/******************************************************************************
 * Author: Brent Briggs
 * Date: 2014-02-13 11:24:16
 *
 * LICENSE:
 * This software is released under the WTF Puplic License as described at
 * www.wtfpl.net. So do WTF you want.
 *
 * DESCRIPTION:
 * Test driver for fileio using the glib testing framework.
 *****************************************************************************/
#include "file.h"
#include <glib.h>

/** Test that new file can be created, opened and closed */
void test_file_open_close() {
    char *filepath = "test_file.txt";
    file_s *file = file_new(filepath, "w+");
    g_assert(file != NULL);
    g_assert((file_free(file)) == 0);
    remove(filepath);
}

/** Test writing to a file */
void test_file_text_read_write() {
    char *filepath = "test_file.txt";
    file_s *file = file_new(filepath, "w+");
    char *test_line = "This is a test line.";
    g_assert((file_put_line(file, test_line)) == 0);

}

int main(int argc, char **argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/tests/file_open_close", test_file_open_close);
    g_test_add_func("/tests/test_file_text_read_write",
            test_file_text_read_write);
    return g_test_run();



    /* Copy the file */

    /* Compare the files */

    /* Append text to file2 */

    /* Count the number of lines in a file. */

    /* test correct line count with non terminated line */

    /* Clear file contents. */

    /* Delete files */
}
