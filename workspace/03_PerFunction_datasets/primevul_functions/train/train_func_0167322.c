delete_entry_thread (GSimpleAsyncResult *result, GDataService *service, GCancellable *cancellable)
{
	gboolean success;
	GError *error = NULL;
	DeleteEntryAsyncData *data = g_simple_async_result_get_op_res_gpointer (result);


	success = gdata_service_delete_entry (service, data->domain, data->entry, cancellable, &error);
	if (success == FALSE) {
		g_simple_async_result_set_from_error (result, error);
		g_error_free (error);
		return;
	}


	g_simple_async_result_set_op_res_gboolean (result, success);
}
