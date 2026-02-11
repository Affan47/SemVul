lcrt_connect_on_selection_changed(GtkWidget *widget, gpointer user_data)
{
    struct lcrt_connect *lconnect = (struct lcrt_connect *)user_data;
    struct lcrt_window *lwindow = lconnect->parent;
    struct lcrtc_user *user;

    debug_where();
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeView *treeview = GTK_TREE_VIEW (lconnect->c_treeview);
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);;
    char *value;
    int sensitive;

    lconnect->connect_button_clicked = FALSE;

    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gtk_widget_set_sensitive(lconnect->c_connectbutton, FALSE);
        return;
    }

    gtk_tree_model_get(model, &iter, 0, &value, -1);
    if (strcmp(value, lconnect->config.value[LCRT_C_SESSION]) != 0) {
        debug_print("select on change: %s\n", value);
        if ((user = lcrt_user_find_by_name(&lwindow->u_config, value)) != NULL) {
            debug_where();
            lcrt_statusbar_set_user(lwindow->w_statusbar, user);
        }
        if (user->is_folder)
            sensitive = FALSE;
        else
            sensitive = TRUE;
    } else {
            sensitive = FALSE;
    }
    gtk_widget_set_sensitive(lconnect->c_connectbutton, sensitive);
    g_free(value);
}
