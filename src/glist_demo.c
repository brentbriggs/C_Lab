#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void print_list_iterator(gpointer item, gpointer prefix)
{
    printf("%s %s\n", prefix, item);
}

int main() {
    GList *list = NULL;
    printf("Append items to the list using g_list_append().\n");
    printf("Print the list using g_list_foreach().\n");
    list = g_list_append(list, "Spruce Pine");
    list = g_list_append(list, "Burnsville");
    list = g_list_append(list, "Flag Pond");
    g_list_foreach(list, print_list_iterator, "-> ");
    printf("\n");
    printf("The list length according to g_list_length() is: %d\n",
            g_list_length(list));

    printf("Remove 'Spruce Pine' using g_list_remove().\n");
    list = g_list_remove(list, "Spruce Pine");
    g_list_foreach(list, print_list_iterator, "-> ");
    printf("\n");

    printf("Create an new list:\n");
    GList *new_list = NULL;
    new_list = g_list_append(new_list, "Micaville");
    new_list = g_list_append(new_list, "Marshall");
    new_list = g_list_append(new_list, "Mars Hill");
    g_list_foreach(new_list, print_list_iterator, "-> ");
    printf("\n");

    printf("Append the second list to the first list with g_list_concat().\n");
    list = g_list_concat(list, new_list);
    g_list_foreach(list, print_list_iterator, "-> ");
    printf("\n");

    printf("Set *list to the last list item using g_list_last().\n");
    list = g_list_last(list);
    printf("list now points to item: %s\n\n", list->data);

    printf("The first item in the list using g_list_first(): %s\n\n",
            g_list_first(list)->data);

    printf("The previous item using g_list_previous(): %s\n\n",
            g_list_previous(list)->data);

    printf("The item two items before the current using g_list_nth_prev(): "\
            "%s\n\n",
            g_list_nth_prev(list, 2)->data); /* The gint arg must be within the
                                                bounds of the list or you will
                                                have a crash */

    list = g_list_first(list);
    printf("Remove a node using a pointer to a the node itself instead of the "\
            "node's data using g_list_remove_link() and g_list_nth().\n");

    GList *removed = g_list_nth(list, 2);
    list = g_list_remove_link(list, removed);
    g_list_free_1(removed);
    g_list_foreach(list, print_list_iterator, "-> ");
    printf("\n");

    printf("Remove and free the first node in one step using "\
            "g_list_delete_link().\n");
    list = g_list_delete_link(list, list);
    g_list_foreach(list, print_list_iterator, "-> ");
    printf("\n");


    printf("Find the position of 'Mars Hill' using g_list_index().\n");
    printf("The item 'Mars Hill' is at position %d.\n\n",
            g_list_index(list, "Mars Hill"));

    printf("Find the position of 'Marshall' using g_list_position()"\
            "and g_list_find().\n");
    GList *target = g_list_find(list, "Marshall");
    printf("The item 'Marshall' is at position %d.\n\n",
            g_list_position(list, target));
}
