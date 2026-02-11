remove_device (GUPnPDeviceInfo *info)
{
        GtkTreeModel *model;
        GtkTreeIter   root_iter;
        GtkTreeIter   iter;
        const char   *udn;

        model = gtk_tree_view_get_model (GTK_TREE_VIEW (treeview));
        g_assert (model != NULL);

        udn = gupnp_device_info_get_udn (info);

        if (!gtk_tree_model_get_iter_first (model, &root_iter))
                return;

        if (find_device (model, udn, &root_iter, &iter)) {
                unschedule_icon_update (info);
                gtk_tree_store_remove (GTK_TREE_STORE (model), &iter);
        }
}
