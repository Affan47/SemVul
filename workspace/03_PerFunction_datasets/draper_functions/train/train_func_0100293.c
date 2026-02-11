_gdc_view_option_changed(GtkComboBox *widget, gpointer user_data)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    gint months_val;

    model = GTK_TREE_MODEL(gtk_combo_box_get_model(widget));
    if (!gtk_combo_box_get_active_iter(widget, &iter))
        return;
    gtk_tree_model_get(model, &iter, VIEW_OPTS_COLUMN_NUM_MONTHS, &months_val, -1);
    g_debug("changing to %d months", months_val);
    gnc_dense_cal_set_num_months(GNC_DENSE_CAL(user_data), months_val);
}
