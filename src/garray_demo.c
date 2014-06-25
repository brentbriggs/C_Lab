#include <glib.h>
#include <stdio.h>

void print_string_array(GArray *garray)
{
    printf("Array Contents:\n");
    for (int i = 0; i < (int)garray->len; i++)
    {
        printf("[%d] => %s \n", i, g_array_index(garray, char *, i ));
    }
}

void print_int_array(GArray *garray)
{
    printf("Array Values: ");
    for (int i = 0; i < (int)garray->len; i++)
    {
        printf(" %d ", g_array_index(garray, int, i));
    }
    printf("\n");
}

int int_comparator(gpointer a, gpointer b)
{
    return *(int *)a - *(int *)b;
}

int main() {
    printf("Setup an array of char * and append items to it.\n");
    char *val1 = "Vader", *val2 = "Obi Wan", *val3 = "R2D2", *val4 = "C3PO";
    GArray *string_array = g_array_new(FALSE, FALSE, sizeof(char *));
    g_array_append_val(string_array, val1);
    g_array_append_val(string_array, val2);
    g_array_append_val(string_array, val3);
    g_array_append_val(string_array, val4);
    print_string_array(string_array);
    printf("\n");
    printf("The array size is %d.\n\n", string_array->len);

    printf("Get first item using g_array_index(): %s\n\n",
            g_array_index(string_array, char*, 0));

    printf("Remove an array item at a specific index using "\
            "g_array_remove_index().\n");
    g_array_remove_index(string_array, 1);
    printf("The array size is %d.\n\n", string_array->len);

    printf("Setup and array of int type with 16 elements.\n");
    GArray *int_array = g_array_sized_new(TRUE, TRUE, sizeof(int), 16);
    printf("Preallocated size is hidden.\n");
    printf("Array size is %d.\n", int_array->len);
    print_int_array(int_array);
    printf("\n");

    printf("Resize the array using g_array_set_size().\n");
    g_array_set_size(int_array, 8);
    printf("Array size is %d.\n", int_array->len);
    print_int_array(int_array);
    printf("\n");

    printf("Add values to the array with g_array_append_vals().\n");
    int x[3] = {1, 2, 3};
    g_array_append_vals(int_array, &x, 3);
    printf("Array size is %d.\n", int_array->len);
    print_int_array(int_array);
    printf("\n");

    printf("Prepend values using g_array_prepend_vals().\n");
    int y[2] = {5, 6};
    g_array_prepend_vals(int_array, &y, 2);
    printf("Array size is %d.\n", int_array->len);
    print_int_array(int_array);
    printf("\n");

    printf("Prepend a single value using g_array_prepend_val().\n");
    int v = 4;
    g_array_prepend_val(int_array, v);
    printf("Array size is %d.\n", int_array->len);
    print_int_array(int_array);
    printf("\n");

    printf("Insert data using g_array_insert_val().\n");
    int a = 33;
    g_array_insert_val(int_array, 6, a);
    printf("Array size is %d.\n", int_array->len);
    print_int_array(int_array);
    printf("\n");

    printf("Insert multiple values using g_array_insert_vals().\n");
    g_array_insert_vals(int_array, 6, y, 2);
    printf("Array size is %d.\n", int_array->len);
    print_int_array(int_array);
    printf("\n");

    printf("Remove a single item using g_array_remove_index().\n");
    g_array_remove_index(int_array, 7);
    printf("Array size is %d.\n", int_array->len);
    print_int_array(int_array);
    printf("\n");

    printf("Remove a range of values using g_array_remove_range().\n");
    g_array_remove_range(int_array, 3, 3);
    printf("Array size is %d.\n", int_array->len);
    print_int_array(int_array);
    printf("\n");

    printf("Remove a single item using g_array_remove_index_fast().\n");
    printf("This function removes the item and replaces it with the last\n" \
            "in the array. NOT COMMONLY USED\n");
    g_array_remove_index_fast(int_array, 6);
    printf("Array size is %d.\n", int_array->len);
    print_int_array(int_array);
    printf("\n");

    printf("Sort the array using g_array_sort() and a comparator function.\n");
    g_array_sort(int_array, (GCompareFunc)int_comparator);
    print_int_array(int_array);
    printf("\n");


    printf("Free the array of ints using g_array_free(int_array, FALSE).\n\n");
    g_array_free(int_array, FALSE);

    printf("Free the array of strings using g_array_free(string_array, TRUE)\n"\
            "so memory for the string pointed to in each element will be\n"\
            "freed.\n");
    g_array_free(string_array, TRUE);
}
