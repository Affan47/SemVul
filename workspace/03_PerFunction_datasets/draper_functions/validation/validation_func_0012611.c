destination_column_formatter (GtkTreeViewColumn *column,
                              GtkCellRenderer *cell,
                              GtkTreeModel *model,
                              GtkTreeIter *iter,
                              ENameSelectorDialog *name_selector_dialog)
{
	EDestinationStore *destination_store = E_DESTINATION_STORE (model);
	EDestination      *destination;
	GString           *buffer;

	destination = e_destination_store_get_destination (destination_store, iter);
	g_assert (destination);

	buffer = g_string_new (e_destination_get_name (destination));

	if (!e_destination_is_evolution_list (destination)) {
		const gchar *email;

		email = e_destination_get_email (destination);
		if (email == NULL || *email == '\0')
			email = "?";
		g_string_append_printf (buffer, " <%s>", email);
	}

	g_object_set (cell, "text", buffer->str, NULL);
	g_string_free (buffer, TRUE);
}
