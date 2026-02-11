dir_symbol_new (const gchar* dirname)
{
	DirSymbol* self = DIR_SYMBOL (g_object_new (DIR_TYPE_SYMBOL, NULL));
	DirSymbolPrivate* priv = DIR_SYMBOL_PRIVATE (self);

	g_assert (dirname != NULL);

	if (!g_file_test (dirname, G_FILE_TEST_IS_DIR))
	{
		g_object_unref (self);
		return NULL;
	}

	priv->self_dir = g_file_new_for_path (dirname);
	gchar *tmp = g_file_get_basename (priv->self_dir);

	if (!tmp || tmp[0] == '.')
	{
		g_free (tmp);
		g_object_unref (self);
		return NULL;
	}
	g_free (tmp);

	GFileInfo *info;
	GFileEnumerator *enumerator = g_file_enumerate_children (priv->self_dir, G_FILE_ATTRIBUTE_STANDARD_NAME, G_FILE_QUERY_INFO_NONE, NULL, NULL);

	if (enumerator == NULL)
	{
		g_object_unref (self);
		return NULL;
	}
	gboolean has_child = FALSE;
	for (info = g_file_enumerator_next_file (enumerator, NULL, NULL); info; info = g_file_enumerator_next_file (enumerator, NULL, NULL))
	{
		const gchar *name = g_file_info_get_name (info);
		if (!name)
		{
			g_object_unref (info);
			continue;
		}
		GFile *file = g_file_get_child (priv->self_dir, name);
		gchar *file_path = g_file_get_path (file);
		g_object_unref (file);
		if (g_file_test (file_path, G_FILE_TEST_IS_DIR))
		{
			DirSymbol *t = dir_symbol_new (file_path);
			g_free (file_path);
			g_object_unref (info);
			if (t)
			{
				g_object_unref (t);
				has_child = TRUE;
				break;
			}
			continue;
		}
		g_free (file_path);
		size_t len = strlen (name);
		if (len <= 3 || strcmp (name + len - 3, ".js") != 0)
		{
			g_object_unref (info);
			continue;
		}
		g_object_unref (info);
		has_child = TRUE;
	}
	g_object_unref (enumerator);
	if (!has_child)
	{
		g_object_unref (self);
		return NULL;
	}

	return self;
}
