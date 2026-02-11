async_data_free (AsyncData *data)
{
	g_object_unref (data->cancellable);
	g_list_free_full (data->files, g_object_unref);

	if (!data->removed)
		data->model->priv->async_handles = g_slist_remove (data->model->priv->async_handles, data);

	g_slice_free (AsyncData, data);
}
