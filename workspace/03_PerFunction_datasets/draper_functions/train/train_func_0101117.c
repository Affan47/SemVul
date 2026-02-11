on_column_remove_clicked (GtkButton *sender, gpointer e)
{
    g_return_if_fail(displayed_columns_view);

    gint i;
    GtkTreeView *view = GTK_TREE_VIEW (displayed_columns_view);
    GtkTreeModel *model = gtk_tree_view_get_model (view);
    GtkTreeIter iter;

    if(!tree_get_current_iter (view, &iter) || !gtk_list_store_iter_is_valid (GTK_LIST_STORE (model), &iter))
        return;

    gtk_tree_model_get (model, &iter, 1, &i, -1);
    gtk_list_store_remove (GTK_LIST_STORE (model), &iter);

    prefs_set_int_index ("col_visible", i, FALSE);
    tm_store_col_order ();
    tm_show_preferred_columns ();
}
