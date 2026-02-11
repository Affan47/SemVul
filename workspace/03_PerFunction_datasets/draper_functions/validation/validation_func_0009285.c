gwy_3d_window_set_labels(GtkWidget *combo,
                         Gwy3DWindow *gwy3dwindow)
{
    gint id;
    Gwy3DLabel *label;

    id = gwy_enum_combo_box_get_active(GTK_COMBO_BOX(combo));
    label = gwy_3d_view_get_label(GWY_3D_VIEW(gwy3dwindow->gwy3dview), id);
    g_return_if_fail(label);

    gtk_entry_set_text(GTK_ENTRY(gwy3dwindow->labels_text),
                       gwy_3d_label_get_text(label));
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(gwy3dwindow->labels_delta_x),
                              label->delta_x);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(gwy3dwindow->labels_delta_y),
                              label->delta_y);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(gwy3dwindow->labels_size),
                              label->size);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gwy3dwindow->labels_autosize),
                                 !label->fixed_size);
}
