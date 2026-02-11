on_button_new_clicked(GtkButton *button, gpointer user_data) {
    OptionsWindow *self = (OptionsWindow *)user_data;
    Profile *profile = Preferences::instance()->create_user_profile(self->_current_profile);
    if (profile == NULL)
        return;

    GtkTreeIter iter;
    GtkTreeModel *model = self->get_selected_tree_iter(&iter);
    if (model == NULL)
        return;

    GtkTreeIter iter_child;
    gtk_tree_store_append(GTK_TREE_STORE(model), &iter_child, &iter);
    gtk_tree_store_set(GTK_TREE_STORE(model), &iter_child,
            TREE_INT_COLUMN, 2,
            TREE_TEXT_COLUMN, profile->get_name(),
            TREE_CONFIG_NAME_COLUMN, profile->get_config_name(),
            TREE_ICON_COLUMN, self->_w.pixbuf_default,
            -1);

    self->expand_and_select(GTK_TREE_VIEW(self->_w.treeview), model, &iter_child);
    gtk_notebook_set_current_page(self->_w.notebook, 0);
}
