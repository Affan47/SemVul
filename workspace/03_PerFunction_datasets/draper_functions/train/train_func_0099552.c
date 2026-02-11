mb_rebuild_ofr_list(gpointer dialog)
{
	GtkListStore *ofr_store;
	GtkWidget *ofr_list;
	GtkScrolledWindow *scw;
	char *titles[] = {"Object", "Band", "Status", "Zpoint", "Err", "Fitted",
			  "Outliers", "MEU", "Airmass", "MJD", NULL};
	int i;
	GtkTreeViewColumn *column;

	ofr_list = gtk_object_get_data(GTK_OBJECT(dialog), "ofr_list");
	if (ofr_list == NULL) {
		scw = gtk_object_get_data(GTK_OBJECT(dialog), "ofr_scw");
		g_return_if_fail(scw != NULL);

		ofr_store = gtk_list_store_new(11, G_TYPE_POINTER,
					       G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
					       G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
					       G_TYPE_STRING, G_TYPE_STRING);

		ofr_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(ofr_store));
		g_object_unref(ofr_store);

		for (i = 0; i < 10; i++) {
			column = gtk_tree_view_column_new_with_attributes(titles[i],
									  gtk_cell_renderer_text_new(),
									  "text", i + 1, NULL);

			gtk_tree_view_column_set_sort_column_id(column, i + 1);
			gtk_tree_view_append_column(GTK_TREE_VIEW(ofr_list), column);
		}

		gtk_scrolled_window_add_with_viewport(scw, ofr_list);
		gtk_widget_ref(ofr_list);
		gtk_object_set_data_full(GTK_OBJECT(dialog), "ofr_list",
					 ofr_list, (GtkDestroyNotify) gtk_widget_destroy);

		gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(ofr_list)),
					    GTK_SELECTION_MULTIPLE);

		gtk_signal_connect(GTK_OBJECT(ofr_list), "button-press-event",
				   GTK_SIGNAL_FUNC(ofr_bpress_cb), dialog);

		gtk_widget_show(ofr_list);
	} else {
		ofr_store = GTK_LIST_STORE (gtk_tree_view_get_model(GTK_TREE_VIEW(ofr_list)));
		gtk_list_store_clear(ofr_store);
	}

	mbds_ofr_to_list(dialog, ofr_list);
}
