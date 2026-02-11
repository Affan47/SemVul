go_component_mime_dialog_init (GOComponentMimeDialog *dlg)
{
	GtkListStore *list = gtk_list_store_new (2, G_TYPE_STRING, G_TYPE_STRING);
	GtkWidget *w = gtk_tree_view_new_with_model (GTK_TREE_MODEL (list));
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GSList *mime_types = go_components_get_mime_types ();
	GSList *l = mime_types;
	GtkTreeIter iter;
	char const *mime_type;

	gtk_dialog_add_buttons (&dlg->base,
	                        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                        GTK_STOCK_OK, GTK_RESPONSE_OK,
	                        NULL);
	gtk_window_set_modal (GTK_WINDOW (dlg), TRUE);
	gtk_window_set_destroy_with_parent (GTK_WINDOW (dlg), TRUE);
	dlg->sel = gtk_tree_view_get_selection (GTK_TREE_VIEW (w));
	g_signal_connect_swapped (w, "button-press-event", G_CALLBACK (button_press_cb), dlg);
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("Object type:", renderer, "text", 0, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (w), column);
	gtk_tree_selection_set_mode (dlg->sel, GTK_SELECTION_BROWSE);
	gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (list), 0, GTK_SORT_ASCENDING);
	while (l) {
		mime_type = (char const *) l->data;
		if (go_components_get_priority (mime_type) >= GO_MIME_PRIORITY_PARTIAL) {
			gtk_list_store_append (list, &iter);
			gtk_list_store_set (list, &iter,
					  0, go_mime_type_get_description (mime_type),
					  1, mime_type,
					  -1);
		}
		l = l->next;
	}
	dlg->list = GTK_TREE_MODEL (list);
	gtk_container_add (GTK_CONTAINER (gtk_dialog_get_content_area (&dlg->base)), w);
	gtk_widget_show_all (gtk_dialog_get_content_area (&dlg->base));
}
