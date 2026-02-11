file_model_filter_file (FileModel* model,
						GFileInfo* file_info)
{
	FileModelPrivate* priv = FILE_MODEL_GET_PRIVATE (model);

	if (priv->filter_hidden && g_file_info_get_is_hidden(file_info))
		return FALSE;
	else if (priv->filter_backup && g_file_info_get_is_backup(file_info))
		return FALSE;
	else if (priv->filter_binary &&
			 g_file_info_get_file_type (file_info) != G_FILE_TYPE_DIRECTORY)
	{
		int i;
		const gchar* name = g_file_info_get_name (file_info);
		for (i = 0; BINARY_SUFFIX[i] != NULL; i++)
		{
			if (g_str_has_suffix (name, BINARY_SUFFIX[i]))
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}
