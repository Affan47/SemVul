add_dict_array(const gchar* const lang_tag, const gchar* const provider_name,
						   const gchar* const provider_desc, const gchar* const provider_file,
						   gpointer user_data)
{
	guint i;
	gchar *result = g_strdup(lang_tag);


	for (i = 0; i < strlen(result); i++)
	{
		if (result[i] == '-')
			result[i] = '_';
	}


	for (i = 0; i < sc_info->dicts->len; i++)
	{
		if (utils_str_equal(g_ptr_array_index(sc_info->dicts, i), result))
			return;
	}

	g_ptr_array_add(sc_info->dicts, result);
}
