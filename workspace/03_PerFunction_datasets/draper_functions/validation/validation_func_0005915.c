set_attributes_callback (GObject *source_object,
			 GAsyncResult *result,
			 gpointer callback_data)
{
	NautilusFileOperation *op;
	GError *error;
	gboolean res;

	op = callback_data;

	error = NULL;
	res = g_file_set_attributes_finish (G_FILE (source_object),
					    result,
					    NULL,
					    &error);

	if (res) {
		g_file_query_info_async (G_FILE (source_object),
					 NAUTILUS_FILE_DEFAULT_ATTRIBUTES,
					 0,
					 G_PRIORITY_DEFAULT,
					 op->cancellable,
					 set_attributes_get_info_callback, op);
	} else {
		nautilus_file_operation_complete (op, NULL, error);
		g_error_free (error);
	}
}
