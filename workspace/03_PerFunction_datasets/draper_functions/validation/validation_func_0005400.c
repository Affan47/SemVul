get_menu_icon_for_file (TreeNode *node,
                        NemoFile *file,
			NemoFileIconFlags flags)
{
	NemoIconInfo *info;
	GIcon *gicon, *emblem_icon, *emblemed_icon;
	GEmblem *emblem;
	GdkPixbuf *pixbuf, *retval;
	gboolean highlight;
	int size;
	FMTreeModel *model;
	GList *emblem_icons, *l;
	char *emblems_to_ignore[3];
	int i;

	size = nemo_get_icon_size_for_stock_size (GTK_ICON_SIZE_MENU);
	gicon = G_ICON (nemo_file_get_icon_pixbuf (file, size, TRUE, flags));

	i = 0;
	emblems_to_ignore[i++] = NEMO_FILE_EMBLEM_NAME_TRASH;

	if (node->parent && node->parent->file) {
		if (!nemo_file_can_write (node->parent->file)) {
			emblems_to_ignore[i++] = NEMO_FILE_EMBLEM_NAME_CANT_WRITE;
		}
	}

	emblems_to_ignore[i++] = NULL;

	emblem = NULL;
	emblem_icons = nemo_file_get_emblem_icons (node->file,
						       emblems_to_ignore);


	for (l = emblem_icons; l != NULL; l = l->next) {
		emblem_icon = l->data;
		if (nemo_icon_theme_can_render (G_THEMED_ICON (emblem_icon))) {
			emblem = g_emblem_new (emblem_icon);
			emblemed_icon = g_emblemed_icon_new (gicon, emblem);

			g_object_unref (gicon);
			g_object_unref (emblem);
			gicon = emblemed_icon;

			break;
		}
	}

	g_list_free_full (emblem_icons, g_object_unref);

	info = nemo_icon_info_lookup (gicon, size);
	retval = nemo_icon_info_get_pixbuf_nodefault_at_size (info, size);
	model = node->root->model;

	g_object_unref (gicon);

	highlight = (g_list_find_custom (model->details->highlighted_files,
	                                 file, (GCompareFunc) nemo_file_compare_location) != NULL);

	if (highlight) {
		pixbuf = eel_create_spotlight_pixbuf (retval);

		if (pixbuf != NULL) {
			g_object_unref (retval);
			retval = pixbuf;
		}
	}

	g_object_unref (info);

	return retval;
}
