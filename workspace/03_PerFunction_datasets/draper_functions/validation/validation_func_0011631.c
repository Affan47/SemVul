fm_places_model_mount_indicator_cell_data_func(GtkCellLayout *cell_layout,
                                           GtkCellRenderer *render,
                                           GtkTreeModel *tree_model,
                                           GtkTreeIter *it,
                                           gpointer user_data)
{
    FmPlacesItem* item = NULL;
    GdkPixbuf* pix = NULL;
    g_return_if_fail(FM_IS_PLACES_MODEL(tree_model));
    gtk_tree_model_get(tree_model, it, FM_PLACES_MODEL_COL_INFO, &item, -1);
    if(item && item->mounted)
        pix = ((FmPlacesModel*)tree_model)->eject_icon;
    g_object_set(render, "pixbuf", pix, NULL);
}
