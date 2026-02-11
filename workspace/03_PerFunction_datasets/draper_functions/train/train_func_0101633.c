mh_remove_missing_folder_items_func(GNode *node, gpointer data)
{
	FolderItem *item;
	gchar *path;

	cm_return_val_if_fail(node->data != NULL, FALSE);

	if (G_NODE_IS_ROOT(node))
		return FALSE;

	item = FOLDER_ITEM(node->data);

	path = folder_item_get_path(item);
	if (!is_dir_exist(path)) {
		debug_print("folder '%s' not found. removing...\n", path?path:"(null)");
		folder_item_remove(item);
	}
	g_free(path);

	return FALSE;
}
