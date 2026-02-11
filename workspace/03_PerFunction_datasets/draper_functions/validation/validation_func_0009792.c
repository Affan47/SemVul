enumerate_dicts (const char * const lang_tag,
		 const char * const provider_name,
		 const char * const provider_desc,
		 const char * const provider_file,
		 void * user_data)
{
	gchar *lang_name;

	GTree *dicts = (GTree *)user_data;

	lang_name = create_name_for_language (lang_tag);
	g_return_if_fail (lang_name != NULL);


	g_tree_replace (dicts, g_strdup (lang_tag), lang_name);
}
