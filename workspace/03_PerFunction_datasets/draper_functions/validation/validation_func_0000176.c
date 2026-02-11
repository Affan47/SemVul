get_doc_parent(GeanyDocument *doc)
{
	gchar *path;
	gchar *dirname = NULL;
	static GtkTreeIter parent;
	GtkTreeModel *model = GTK_TREE_MODEL(store_openfiles);
	static GdkPixbuf *dir_icon = NULL;

	if (!documents_show_paths)
		return NULL;

	path = g_path_get_dirname(DOC_FILENAME(doc));
	dirname = get_doc_folder(path);

	if (gtk_tree_model_get_iter_first(model, &parent))
	{
		do
		{
			if (find_tree_iter_dir(&parent, dirname))
			{
				g_free(dirname);
				g_free(path);
				return &parent;
			}
		}
		while (gtk_tree_model_iter_next(model, &parent));
	}

	if (!dir_icon)
		dir_icon = ui_get_mime_icon("inode/directory", GTK_ICON_SIZE_MENU);

	gtk_tree_store_append(store_openfiles, &parent, NULL);
	gtk_tree_store_set(store_openfiles, &parent, DOCUMENTS_ICON, dir_icon,
		DOCUMENTS_FILENAME, path,
		DOCUMENTS_SHORTNAME, doc->file_name ? dirname : GEANY_STRING_UNTITLED, -1);

	g_free(dirname);
	g_free(path);
	return &parent;
}
