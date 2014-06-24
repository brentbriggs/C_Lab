#include <glib.h>
#include <stdio.h>

gboolean val_finder(gpointer key, gpointer value, gpointer user_data)
{
    return (g_str_equal(key, user_data));
}

gboolean key_finder(gpointer key, gpointer value, gpointer user_data)
{
    return (g_str_equal(value, user_data));
}

void print_iterator(gpointer key, gpointer value, gpointer user_data)
{
    printf(user_data, key, value);
}

void print_slist_iterator(gpointer item, gpointer prefix)
{
    printf("%s \"%s\"", prefix, item);
}

void print_multi(gpointer key, gpointer value, gpointer user_data)
{
    printf("=> %s:", key);
    g_slist_foreach((GSList *)value, (GFunc)print_slist_iterator, " ");
    printf("\n");
}

void key_destroy_notify(gpointer data)
{
    printf("Got a key destroy call for \"%s\"\n", data);
}

void destroy_multi(gpointer key, gpointer value, gpointer data)
{
    printf("Free value list:");
    g_slist_foreach((GSList *)value, (GFunc)print_slist_iterator, " ");
    printf("\n");
    g_slist_free(value);
}

gboolean stealer(gpointer key, gpointer value, gpointer user_data)
{
    /* Steal all items who's keys start with 'B' or 'M'. */
    return (((char *)key)[0] == 'M' || ((char *)key)[0] == 'B');
}

int main() {
    printf("Create a new hash table with g_hash_table_new_full().\n");
    GHashTable *hash = g_hash_table_new_full(g_str_hash,
                                        g_str_equal,
                                        (GDestroyNotify)key_destroy_notify,
                                        NULL);
    printf("Enter three items into the hahstable.\n");
    g_hash_table_insert(hash, "Yancey", "Burnsville");
    g_hash_table_insert(hash, "Madison", "Marshall");
    g_hash_table_insert(hash, "Buncombe", "Asheville");
    printf("Use g_hash_table_foreach() to print the table contents.\n");
    printf("Hash Table Contents:\n");
    g_hash_table_foreach(hash, (GHFunc)print_iterator, "- Key: %s Value: %s\n");
    printf("\n");

    printf("The number of keys according to g_hash_table_size() is: %d\n\n",
            g_hash_table_size(hash));
    printf("Look up a value for a key using g_hash_table_lookup().\n");
    printf("The value for key 'Madison' is: %s\n\n",
            g_hash_table_lookup(hash, "Madison"));

    printf("Remove a key\\value using g_hash_table_remove().\n");
    gboolean removed = g_hash_table_remove(hash, "Madison");
    printf("The value 'Madison' was %sfound and removed.\n\n",
            removed ? "": "not ");

    printf("Calling g_hash_table_insert() with new_key=\"Yancey\".\n");
    char *new_key = g_strdup("Yancey"); /* Leaves duplicate key in place */
    g_hash_table_insert(hash, new_key, "Burnsville");
    printf("\n");

    printf("Hash Table Contents:\n");
    g_hash_table_foreach(hash, (GHFunc)print_iterator, "- Key: %s Value: %s\n");
    printf("\n");

    printf("Calling g_hash_table_replace() with new_key=\"Yancey\".\n");
    g_hash_table_replace(hash, new_key, "Cat Lick"); /* Removes duplicate key */
    printf("\n");

    printf("Hash Table Contents:\n");
    g_hash_table_foreach(hash, (GHFunc)print_iterator, "- Key: %s Value: %s\n");
    printf("\n");

    printf("Find an item using g_hash_table_find() for key 'Yancey'.\n");
    gpointer item_ptr = g_hash_table_find(hash, (GHRFunc)val_finder, "Yancey");
    printf("Item: %s\n\n", item_ptr);

    printf("Find an item using g_hash_table_find() for value 'Asheville'.\n");
    item_ptr = g_hash_table_find(hash, (GHRFunc)key_finder, "Asheville");
    printf("Item: %s\n\n", item_ptr);

    printf("Look for non existant an item using g_hash_table_find().\n");
    item_ptr = g_hash_table_find(hash, (GHRFunc)val_finder, "Nowhere");
    printf("Item: %s\n\n", item_ptr);

    printf("Find an item using g_hash_table_lookup() for value 'Buncombe'.\n");
    item_ptr = g_hash_table_lookup(hash, "Buncombe");
    printf("Item: %s\n\n", item_ptr);

    printf("Rebuild the list.\n");
    g_hash_table_insert(hash, "Mitchell", "Bakersville");
    g_hash_table_insert(hash, "Avery", "Blowing Rock");
    g_hash_table_insert(hash, "Watauga", "Boone");
    g_hash_table_insert(hash, "Yancey", "Burnsville");
    printf("Hash Table Contents:\n");
    g_hash_table_foreach(hash, (GHFunc)print_iterator, "- Key: %s Value: %s\n");
    printf("\n");

    printf("Remove item using g_hash_table_steal(), No callbacks will be"\
            " called.\n");
    if(g_hash_table_steal(hash, "Avery"))
        printf("Avery has been stolen, you should see no callbacks.\n");

    printf("%d items remaining.\n", g_hash_table_size(hash));
    g_hash_table_foreach(hash, (GHFunc)print_iterator, "- Key: %s Value: %s\n");
    printf("\n");


    printf("Steal items using g_hash_table_foreach_steal().\n");
    g_hash_table_foreach_steal(hash, (GHRFunc)stealer, NULL);
    printf("%d items remaining.\n", g_hash_table_size(hash));
    g_hash_table_foreach(hash, (GHFunc)print_iterator, "- Key: %s Value: %s\n");
    printf("\n");

    printf("Find key\\value pairs using g_hash_table_lookup_extended().\n");
    char *key = NULL;
    char *value = NULL;
    gboolean result = g_hash_table_lookup_extended(hash, "Watauga",
            (gpointer *)&key, (gpointer *)&value);
    if (result)
    {
        printf("Found Key: %s and Value: %s.\n\n", key, value);
    }

    printf("Free the hash table memory with g_hash_table_destroy().\n");
    g_hash_table_destroy(hash);
    g_free(new_key);

    printf("Handle multiple values for a key by using a GSList as the "\
            "value and appending items to it.\n");
    printf("Create a new hashtable.\n");
    hash = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(hash, "Yancey",
            g_slist_append(g_hash_table_lookup(hash, "Yancey"), "Cat Tail"));
    g_hash_table_insert(hash, "Yancey",
            g_slist_append(g_hash_table_lookup(hash, "Yancey"), "Possum Trot"));
    g_hash_table_insert(hash, "Yancey",
            g_slist_append(g_hash_table_lookup(hash, "Yancey"), "Buladean"));
    g_hash_table_insert(hash, "Madison",
            g_slist_append(g_hash_table_lookup(hash, "Madison"), "Flag Pond"));
    g_hash_table_insert(hash, "Madison",
            g_slist_append(g_hash_table_lookup(hash, "Madison"), "Marshall"));

    printf("Hash Table Contents:\n");
    g_hash_table_foreach(hash, print_multi, NULL);

    printf("\n");
    printf("Destroy the hash table.\n");
    g_hash_table_foreach(hash, destroy_multi, NULL);
    g_hash_table_destroy(hash);

    return 0;
}
