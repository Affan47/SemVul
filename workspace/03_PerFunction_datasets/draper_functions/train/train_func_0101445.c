columns_bios_set_properties (GtkTreeViewColumn *column,
                             GtkCellRenderer *renderer,
                             GtkTreeModel *model,
                             GtkTreeIter *iter)
{
        GvaGameStoreColumn column_id;
        gchar *bios, *cp;
        gsize length;

        column_id = gtk_tree_view_column_get_sort_column_id (column);
        gtk_tree_model_get (model, iter, column_id, &bios, -1);


        length = strlen (bios);
        cp = bios + length - 5;
        if (g_ascii_strcasecmp (cp, " BIOS") == 0)
                *cp = '\0';

        g_object_set (renderer, "text", bios, NULL);

        g_free (bios);
}
