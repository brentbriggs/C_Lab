#include <glib.h>
#include <stdio.h>

gint finder(gpointer key, gpointer user_data)
{
    if(g_str_equal((char *)key, "i"))
        return 0;
    else
        return 1;
}
void destroy_key(gpointer data)
{
    printf("Key %s destroyed.\n", data);
}

void destroy_val(gpointer data)
{
    printf("Value %s destroyed.\n", data);
}

gboolean print_iterator(gpointer key, gpointer value, gpointer data)
{
    printf("=> %s: %s\n", key, value);
    return FALSE;
}

int main() {
    printf("Create a new GTree using g_tree_new_full().\n");
    GTree *tree = g_tree_new_full((GCompareDataFunc)g_ascii_strcasecmp, NULL,
            (GDestroyNotify)destroy_key, (GDestroyNotify)destroy_val);
    printf("Add items to the tree.\n");
    g_tree_insert(tree, "c", "Captain America");
    g_tree_insert(tree, "i", "Iron Man");
    g_tree_insert(tree, "h", "Hawk Eye");
    g_tree_insert(tree, "s", "Spider Man");
    printf("Tree height from g_tree_height(): %d\n", g_tree_height(tree));
    printf("Number of nodes from g_tree_nnodes(): %d\n", g_tree_nnodes(tree));
    printf("List the tree using g_tree_foreach() and a GTraverseFunc.\n");
    printf("Tree Contents:\n");
    g_tree_foreach(tree, (GTraverseFunc)print_iterator, NULL);
    printf("\n");

    printf("Find items using g_tree_lookup().\n");
    printf("The data at 'i' is '%s'\n", g_tree_lookup(tree, "i"));
    printf("%s\n\n", g_tree_lookup(tree, "d") ?
            "Unexpected value!!" : "No data found for 'd'");

    printf("Find items using g_tree_search() and a GCompareFunc.\n");
    gpointer val = g_tree_search(tree, (GCompareFunc)finder, NULL);
    printf("The value is %s\n\n", val);

    printf("Remove an item using g_tree_remove().\n");
    g_tree_remove(tree, "h");
    printf("Number of nodes is now: %d\n", g_tree_nnodes(tree));
    printf("Tree Contents:\n");
    g_tree_foreach(tree, (GTraverseFunc)print_iterator, NULL);
    printf("\n");

    printf("Replacing 's', destroy functions will be called.\n");
    g_tree_replace(tree, "s", "Storm");
    printf("Number of nodes is now: %d\n", g_tree_nnodes(tree));
    printf("Tree Contents:\n");
    g_tree_foreach(tree, (GTraverseFunc)print_iterator, NULL);
    printf("\n");

    printf("Stealing 'c' with g_tree_steal(), no drstroy functions now.\n");
    g_tree_steal(tree, "c");
    printf("Number of nodes is now: %d\n", g_tree_nnodes(tree));
    printf("Tree Contents:\n");
    g_tree_foreach(tree, (GTraverseFunc)print_iterator, NULL);
    printf("\n");

    printf("Destroying the tree using g_tree_destroy().\n");
    g_tree_destroy(tree);
}
