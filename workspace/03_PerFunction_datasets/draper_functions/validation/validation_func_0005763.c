gog_theme_edit (GogTheme *theme, GOCmdContext *cc)
{
	struct theme_edit_state state;
	GtkWidget *w;

	if (!GOG_IS_THEME (theme)) {

		GtkBuilder *gui = go_gtk_builder_load_internal ("res:go:graph/new-theme-prefs.ui", GETTEXT_PACKAGE, cc);
		int response;
		GtkWidget *w;
		GtkListStore *l = GTK_LIST_STORE (gtk_builder_get_object (gui, "classes-list"));
		GtkTreeView *tv = GTK_TREE_VIEW (gtk_builder_get_object (gui, "classes-tree"));
		GtkCellRenderer *renderer;
		GtkTreeViewColumn *column;
		GtkTreeIter iter;
		unsigned i;

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (_("Class"), renderer, "text", 0, NULL);
		gtk_tree_view_append_column (tv, column);
		renderer = gtk_cell_renderer_toggle_new ();
		column = gtk_tree_view_column_new_with_attributes (_("Create"), renderer, "active", 1, NULL);
		gtk_tree_view_append_column (tv, column);
		for (i = 0; i < G_N_ELEMENTS (roles); i++) {
			if (!strcmp (roles[i].klass_name, "Series"))
				continue;
			gtk_list_store_append (l, &iter);
			gtk_list_store_set (l, &iter, 0, _(roles[i].label), 1, FALSE, 2, i, -1);
		}
		g_signal_connect_swapped (renderer, "toggled", G_CALLBACK (create_toggled_cb), l);

		w = go_gtk_builder_get_widget (gui, "new-theme-prefs");
		response = gtk_dialog_run (GTK_DIALOG (w));
		gtk_widget_destroy (w);
		g_object_unref (gui);
		if (response == 1) {
			theme = gog_theme_new (_("New theme"), FALSE);
			theme->id = go_uuid ();
			theme->type = GO_RESOURCE_RW;
		} else
			return NULL;
	}

	state.theme = theme;
	state.gui = go_gtk_builder_load_internal ("res:go:graph/gog-theme-editor.ui", GETTEXT_PACKAGE, cc);

	w = go_gtk_builder_get_widget (state.gui, "gog-theme-editor");
	if (gtk_dialog_run (GTK_DIALOG (w))) {
	}
	gtk_widget_destroy (w);
	g_object_unref (state.gui);
	return NULL;
}
