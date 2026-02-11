vcal_item_destroy(Folder *folder, FolderItem *_item)
{
	VCalFolderItem *item = (VCalFolderItem *)_item;
	g_return_if_fail(item != NULL);
	g_free(item);
}
