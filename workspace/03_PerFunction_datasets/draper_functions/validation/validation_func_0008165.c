on_spell_window_size_allocate(GtkWidget *widget, gpointer user_data) {
    guint i;
    guint width;
    gboolean valid;
    GtkTreeIter iter;
    guint column_count;
    GList *column_list;
    GtkTreeViewColumn *column;


    if (!has_init) return;


    width = spell_treeview->allocation.width;


    column_list = gtk_tree_view_get_columns(GTK_TREE_VIEW(spell_treeview));
    column_count = g_list_length(column_list);


    for (i = 0; i < column_count - 1; i += 1) {
        column = g_list_nth_data(column_list, i);
        width -= gtk_tree_view_column_get_width(column);
    }


    g_list_free(column_list);


    g_object_set(G_OBJECT(description_renderer), "wrap-width", width, NULL);


    valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(spell_store), &iter);
    while (valid) {
        GtkTreePath *tree_path;

        tree_path =
            gtk_tree_model_get_path(GTK_TREE_MODEL(spell_store), &iter);
        gtk_tree_model_row_changed(
            GTK_TREE_MODEL(spell_store), tree_path, &iter);
        gtk_tree_path_free(tree_path);
        valid =
            gtk_tree_model_iter_next(GTK_TREE_MODEL(spell_store), &iter);
    }
}
