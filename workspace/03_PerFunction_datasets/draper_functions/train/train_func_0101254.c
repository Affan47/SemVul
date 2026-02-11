set_status_data_free (gpointer data)
{
	SetStatusData *status_data = data;

	g_free (status_data->primary_status);
	g_free (status_data->detail_status);

	g_slice_free (SetStatusData, data);
}
