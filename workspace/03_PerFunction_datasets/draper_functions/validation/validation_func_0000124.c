gitg_dnd_data_free (GitgDndData *data)
{
	gtk_target_list_unref (data->target_list);
	gtk_target_list_unref (data->revision_target_list);

	remove_scroll_timeout (data);

	g_slice_free (GitgDndData, data);
}
