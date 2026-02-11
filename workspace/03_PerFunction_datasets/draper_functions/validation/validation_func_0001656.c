gwy_enum_combo_box_update_int(GtkComboBox *combo,
                              gint *integer)
{
    GwyInventoryStore *store;
    const GwyEnum *item;
    gint i;

    i = gtk_combo_box_get_active(combo);
    store = GWY_INVENTORY_STORE(gtk_combo_box_get_model(combo));
    g_return_if_fail(GWY_IS_INVENTORY_STORE(store));
    item = gwy_inventory_get_nth_item(gwy_inventory_store_get_inventory(store),
                                      i);
    g_return_if_fail(item);
    *integer = item->value;
}
