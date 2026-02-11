_gnc_item_find_selection(GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, gpointer data)
{
    FindSelectionData *to_find = (FindSelectionData*)data;
    gchar *iterStr;
    gboolean found;

    gtk_tree_model_get(model, iter, 0, &iterStr, -1);
    found = g_strcmp0(to_find->string_to_find, iterStr) == 0;
    g_free(iterStr);
    if (found)
    {
        to_find->found_path = gtk_tree_path_copy(path);
        return TRUE;
    }
    return FALSE;
}
