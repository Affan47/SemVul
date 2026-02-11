active_toggled_cb (GtkCellRendererToggle *cell,
                   gchar                 *path_str,
                   ArioPluginManager     *pm)
{
        GtkTreeIter iter;
        GtkTreePath *path;
        GtkTreeModel *model;

        path = gtk_tree_path_new_from_string (path_str);

        model = gtk_tree_view_get_model (GTK_TREE_VIEW (pm->priv->tree));
        g_return_if_fail (model != NULL);

        gtk_tree_model_get_iter (model, &iter, path);

        if (&iter != NULL)
                plugin_manager_toggle_active (pm, &iter, model);

        gtk_tree_path_free (path);
}
