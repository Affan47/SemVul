for_each_child__for_each_file_func (GFile     *file,
				    GFileInfo *info,
				    gpointer   user_data)
{
	ForEachChildData *data = user_data;
	GthFileData      *file_data;

	file_data = gth_file_source_get_file_data (data->file_source, file, info);
	if (file_data == NULL)
		return;

	data->for_each_file_func (file_data->file, file_data->info, data->user_data);

	if (data->recursive && (g_file_info_get_file_type (file_data->info) == G_FILE_TYPE_DIRECTORY))
		data->to_visit = g_list_append (data->to_visit, g_object_ref (file_data));

	g_object_unref (file_data);
}
