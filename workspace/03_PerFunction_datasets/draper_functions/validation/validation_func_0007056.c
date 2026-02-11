check_direction(const gchar * filename, gint dir)
{
    GlivImage **prev, **next;
    GList *next_node;

    if (dir == 1) {
        prev = &previous_image;
        next = &next_image;

        next_node = current_image->node->next;
        if (next_node != NULL)
            next_node = next_node->next;
    } else {

        prev = &next_image;
        next = &previous_image;

        next_node = current_image->node->prev;
        if (next_node != NULL)
            next_node = next_node->prev;
    }

    if (*next == NULL)
        return FALSE;


    if (filename == (*next)->node->data) {
        load_direction(dir);
        return TRUE;
    }


    if (next_node != NULL && filename == next_node->data) {
        GlivImage *new;

        if (*prev != NULL)
            g_object_unref(*prev);
        *prev = *next;
        *next = NULL;

        new = load_file(filename, NULL);
        if (new == NULL) {
            remove_from_list(next_node);
            return TRUE;
        }

        new->node = next_node;

        render_next_image(new);
        g_object_unref(new);
        return TRUE;
    }

    return FALSE;
}
