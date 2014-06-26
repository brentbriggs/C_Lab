#include <glib.h>
#include <stdio.h>

void print_iterator(gpointer item)
{
    printf("=> %s\n", item);
}

gint sorter(gconstpointer a, gconstpointer b, gconstpointer data)
{
    return(g_strcmp0(a, b));
}

int main() {
    printf("Create a new GQueue.\n");
    GQueue *queue = g_queue_new();
    printf("Empty Queue by g_queue_is_empty(): %s\n",
            g_queue_is_empty(queue) ? "EMPTY" : "NOT EMPTY");
    printf("Add items to the back of the queue using g_queue_push_tail().\n");
    g_queue_push_tail(queue, "Mickey");
    g_queue_push_tail(queue, "Minnie");
    g_queue_push_tail(queue, "Donald");
    g_queue_push_tail(queue, "Daisy");
    g_queue_push_tail(queue, "Goofy");
    printf("Print the queue using g_queue_foreach().\n");
    g_queue_foreach(queue, (GFunc)print_iterator, NULL);
    printf("\n");

    printf("Sort the list using g_queue_sort() and a GCompareDataFunc.\n");
    g_queue_sort(queue, (GCompareDataFunc)sorter, NULL);
    printf("Queue Contents:\n");
    g_queue_foreach(queue, (GFunc)print_iterator, NULL);
    printf("\n");

    printf("Top of the queue with g_queue_peek_head(): %s\n",
            g_queue_peek_head(queue));
    printf("Bottom of the queue with g_queue_peek_tail(): %s\n",
            g_queue_peek_tail(queue));
    printf("Length of queue with g_queue_get_length(): %d\n\n",
            g_queue_get_length(queue));

    printf("Remove '%s' with g_queue_pop_head().\n",
            g_queue_pop_head(queue));
    printf("Queue Length: %d\n", g_queue_get_length(queue));
    printf("Queue Contents:\n");
    g_queue_foreach(queue, (GFunc)print_iterator, NULL);
    printf("\n");

    printf("Add to the front of the queue with g_queue_push_head().\n");
    g_queue_push_head(queue, "Pluto");
    printf("Top of the queue with g_queue_peek_head(): %s\n",
            g_queue_peek_head(queue));
    printf("Queue Contents:\n");
    g_queue_foreach(queue, (GFunc)print_iterator, NULL);
    printf("\n");

    printf("Find 'Goofy' in the queue using g_queue_find().\n");
    GList *link = g_queue_find(queue, "Goofy");
    printf("Remove 'Goofy' using g_queue_unlink().\n");
    g_queue_unlink(queue, link);
    g_list_free(link);
    printf("Queue Contents:\n");
    g_queue_foreach(queue, (GFunc)print_iterator, NULL);
    printf("\n");

    printf("Remove 'Minnie' using g_queue_remove().\n");
    g_queue_remove(queue, "Minnie");
    printf("Queue Contents:\n");
    g_queue_foreach(queue, (GFunc)print_iterator, NULL);
    printf("\n");

    printf("Free the queue with g_queue_free().\n");
    g_queue_free(queue);
}
