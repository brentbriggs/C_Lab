/******************************************************************************
 * Author: Brent Briggs (brent.briggs@gmail.com)
 * Date: 2014-06-16 14:38:41
 *
 * LICENSE:
 * This software is released under the WTF Puplic License as described at
 * www.wtfpl.net. So do WTF you want.
 *
 * DESCRIPTION:
 * Example of usage of the singly linked list GSList in the glib library.
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct {
    char* name;
    int shoe_size;
} Person;

/* gpointer is a typedef for void * in glib */
void print_list_iterator(gpointer item, gpointer prefix)
{
    printf("%s %s\n", prefix, item);
}

void print_person_list(gpointer item, gpointer seperator)
{
    Person *person = (Person *)item;
    printf("(%s) %s Shoe Size: %i\n",
            person->name,
            seperator,
            person->shoe_size);
}

gint string_comparator(gconstpointer item1, gconstpointer item2) {
    return g_ascii_strcasecmp(item1, item2);
}

gint custom_finder(gconstpointer target, gconstpointer item)
{
    return g_ascii_strcasecmp(item, target);
}


int main() {
    /* List manipulation. */
    GSList *list = NULL; /* Create an empty list. */
    printf("Created an empty singly linked list called \"list\".\n");
    printf("Get the list length using g_slist_length():\n");
    printf("The list is now %d items long.\n", g_slist_length(list));
    printf("\n");

    printf("Append items \"first\", \"second\", and \"third\" to the list.\n");
    list = g_slist_append(list, "first"); /* Append items to the list. */
    list = g_slist_append(list, "second");
    list = g_slist_append(list, "third");
    printf("The last item is '%s'\n", g_slist_last(list)->data);
    printf("The item at index '1' is '%s'\n", g_slist_nth(list, 1)->data);
    printf("Now the item at index '1' using g_slist_nth_data(): '%s'\n",
            g_slist_nth_data(list, 1));
    printf("And the 'next' item after first item using g_slist_next() '%s'\n",
            g_slist_next(list)->data);
    printf("The list is now %d items long.\n", g_slist_length(list));
    printf("\n");

    /* Itterating over a list - no function */
    printf("Print list contents with simple iteration:\n");
    GSList *iterator = NULL;
    for(iterator = list; iterator != NULL; iterator = iterator->next)
    {
        printf("- %s\n", iterator->data);
    }
    printf("\n");

    /* Itterating with a function */
    printf("Print list contents using iteration with g_slist_foreach():\n");
    /* Itterating over a list - with function; the prefix is configurable */
    g_slist_foreach(list, print_list_iterator, "-> ");
    printf("\n");


    printf("Prepend the item 'zeroth' to the list using g_slist_prepend.\n");
    list = g_slist_prepend(list, "zeroth"); /* Prepend to head of list. */
    printf("The list is now %d items long.\n", g_slist_length(list));
    printf("The item at index '0' is '%s'\n", g_slist_nth(list, 0)->data);
    printf("List Contents:\n");
    g_slist_foreach(list, print_list_iterator, "-> ");
    printf("\n");

    /* Dealing with duplicates */
    printf("Adding duplicates.\n");
    list = g_slist_append(list, "second");
    list = g_slist_append(list, "third");
    list = g_slist_append(list, "third");
    printf("The list is now %d items long.\n", g_slist_length(list));
    printf("List Contents:\n");
    g_slist_foreach(list, print_list_iterator, "-> ");
    printf("\n");
    printf("Remove first occurance of 'second' using g_slist_remove().\n");
    list = g_slist_remove(list, "second");
    printf("Remove all occurances of 'third' using g_slist_remove_all().\n");
    list = g_slist_remove_all(list, "third");
    printf("List Contents:\n");
    g_slist_foreach(list, print_list_iterator, "-> ");
    printf("\n");

    /* Combining lists*/
    printf("Create a second list with contents:\n");
    GSList *list2 = NULL;
    list2 = g_slist_append(list2, "third");
    list2 = g_slist_append(list2, "fourth");
    list2 = g_slist_append(list2, "fifth");
    g_slist_foreach(list, print_list_iterator, "-> ");
    printf("\n");

    printf("Combine the lists using g_slist_concat()\n");
    GSList *both = g_slist_concat(list, list2);
    printf("Combined List Contents:\n");
    g_slist_foreach(both, print_list_iterator, "-> ");
    printf("\n");

    /* Reversing a list */
    printf("Reverse list using g_slist_reverse():\n");
    GSList *reverse = g_slist_reverse(both);
    printf("Reversed List Contents:\n");
    g_slist_foreach(reverse, print_list_iterator, "-> ");
    printf("\n");

    printf("Free all lists from memory using g_slist_free().\n");
    g_slist_free(both);
    g_slist_free(reverse);
    g_slist_free(list);
    g_slist_free(list2);
    printf("\n");

    /* User defined types */
    printf("Using lists with user defined data structures:\n");
    printf("typedef struct {\n");
    printf("    char* name;\n");
    printf("    int shoe_size;\n");
    printf("} Person;\n");
    printf("\n");

    list = NULL;

    printf("Create Person Bob with shoe size 12 and add him to the list.\n");
    Person *bob = (Person *)malloc(sizeof(Person));
    bob->name = "Bob";
    bob->shoe_size = 12;
    list = g_slist_append(list, bob);


    printf("Create Person Jeb with shoe size 10 and add him to the list.\n");
    printf("Use g_new() to create Person *jeb instead of malloc()\n");
    Person *jeb = g_new(Person, 1); /* Use g_new instead of malloc */
    jeb->name = "Jeb";
    jeb->shoe_size = 10;
    list = g_slist_append(list, jeb);
    printf("\n");
    printf("Person List Contents:\n");
    g_slist_foreach(list, print_person_list, " => ");
    printf("\n");

    printf("Tom's shoe size is '%d'\n", ((Person*)list->data)->shoe_size);
    printf("The last Person's name is '%s'\n",
           ((Person*)g_slist_last(list)->data)->name);

    g_slist_free(list);
    free(bob);
    g_free(jeb); /* Glib enhanced wrapper for free() function */

    printf("\n");
    printf("Create new list\n");
    list = NULL;
    list = g_slist_append(list, "Raleigh");
    list = g_slist_append(list, "Asheville");
    list = g_slist_append(list, "Burnsville");
    list = g_slist_append(list, "Micaville");
    list = g_slist_append(list, "Bakersville");
    g_slist_foreach(list, print_list_iterator, "=>");

    printf("Use g_list_sort() to sort the list\n");
    list = g_slist_sort(list, (GCompareFunc)string_comparator);
    g_slist_foreach(list, print_list_iterator, "=>");
    printf("\n");

    printf("Find an element using g_slist_find().\n");
    GSList *item = g_slist_find(list, "Burnsville");
    printf("This should be the third item '%s'.\n\n", item->data);
    printf("Look for 'Las Angeles' using g_slist_find().\n");
    item = g_slist_find(list, "Las Angeles");
    printf("'Las Angeles' is not in the list so we get: %s\n\n",
            item ? item->data : "(null)");
    printf("find 'Bakersville' using g_slist_find_custom().\n");
    item = g_slist_find_custom(list,
                               "Bakersville",
                               (GCompareFunc)custom_finder);
    printf("This should be the second item in the list: %s\n\n", item->data);

    printf("Insert 'Spruce Pine' using g_slist_insert_sorted().\n");
    list = g_slist_insert_sorted(list,
                                 "Spruce Pine",
                                 (GCompareFunc)g_ascii_strcasecmp);
    g_slist_foreach(list, print_list_iterator, "=>");
    printf("\n");

    printf("Insert 'Brevard' in the second position using g_slist_insert().\n");
    list = g_slist_insert(list, "Brevard", 1);
    g_slist_foreach(list, print_list_iterator, "=>");
    printf("\n");


    printf("Insert 'Greenville' before 'Raleigh' using g_slist_instert_before().\n");
    list = g_slist_insert_before(list,
                                g_slist_find(list, "Raleigh"),
                                "Greenville");
    g_slist_foreach(list, print_list_iterator, "=>");
    printf("\n");


    return 0;
}
