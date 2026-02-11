gwy_inventory_store_iter_nth_child(GtkTreeModel *model,
                                   GtkTreeIter *iter,
                                   GtkTreeIter *parent,
                                   gint n)
{
    GwyInventoryStore *store;

    store = GWY_INVENTORY_STORE(model);

    if (parent)
        return FALSE;

    if (n < gwy_inventory_get_n_items(store->inventory)) {
        iter->stamp = store->stamp;
        iter->user_data = gwy_inventory_get_nth_item(store->inventory, n);
        iter->user_data2 = GUINT_TO_POINTER(n);
        return TRUE;
    }
    return FALSE;
}
