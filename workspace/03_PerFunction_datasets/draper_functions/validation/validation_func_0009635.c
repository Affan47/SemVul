cryptui_key_combo_get_key_store (GtkComboBox *ckcombo)
{
    GtkTreeModel *model = gtk_combo_box_get_model (ckcombo);
    g_return_val_if_fail (CRYPTUI_KEY_STORE (model), NULL);
    return CRYPTUI_KEY_STORE (model);
}
