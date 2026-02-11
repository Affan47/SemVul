keyword_add_from_config(GtkTreeStore *keyword_tree, GtkTreeIter *parent, const gchar **attribute_names, const gchar **attribute_values)
{
	gchar *name = NULL;
	gboolean is_kw = TRUE;

	while (*attribute_names)
		{
		const gchar *option = *attribute_names++;
		const gchar *value = *attribute_values++;

		if (READ_CHAR_FULL("name", name)) continue;
		if (READ_BOOL_FULL("kw", is_kw)) continue;

		log_printf("unknown attribute %s = %s\n", option, value);
		}
	if (name && name[0])
		{
		GtkTreeIter iter;

		if (!keyword_exists(GTK_TREE_MODEL(keyword_tree), parent, NULL, name, FALSE, &iter))
			{
			gtk_tree_store_append(keyword_tree, &iter, parent);
			}
		keyword_set(keyword_tree, &iter, name, is_kw);
		g_free(name);
		return gtk_tree_iter_copy(&iter);
		}
	g_free(name);
	return NULL;
}
