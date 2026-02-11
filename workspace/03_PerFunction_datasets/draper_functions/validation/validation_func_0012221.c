on_name_field_changed (GtkEditable *editable,
		       gpointer     user_data)
{
	GtkTreeIter   iter;
	g_return_if_fail(GTK_IS_TREE_VIEW(bookmark_list_widget));
	g_return_if_fail(GTK_IS_ENTRY(name_field));

	if (!get_selection_exists())
		return;


	gtk_tree_selection_get_selected (bookmark_selection,
					 NULL,
					 &iter);

	gtk_list_store_set (bookmark_list_store,
			    &iter, BOOKMARK_LIST_COLUMN_NAME,
			    gtk_entry_get_text (GTK_ENTRY (name_field)),
			    -1);
	text_changed = TRUE;
	name_text_changed = TRUE;
}
