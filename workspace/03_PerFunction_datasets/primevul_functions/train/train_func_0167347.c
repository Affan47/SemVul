insert_entry_thread (GSimpleAsyncResult *result, GDataService *service, GCancellable *cancellable)
{
	GDataEntry *updated_entry;
	GError *error = NULL;
	InsertEntryAsyncData *data = g_simple_async_result_get_op_res_gpointer (result);


	updated_entry = gdata_service_insert_entry (service, data->domain, data->upload_uri, data->entry, cancellable, &error);
	if (updated_entry == NULL) {
		g_simple_async_result_set_from_error (result, error);
		g_error_free (error);
		return;
	}


	g_simple_async_result_set_op_res_gpointer (result, updated_entry, (GDestroyNotify) g_object_unref);
}
