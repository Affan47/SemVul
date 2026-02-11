folder_unref_account_func(GNode *node, gpointer data)
{
	FolderItem *item = node->data;
	PrefsAccount *account = data;

	if (item->account == account)
		item->account = NULL;

	return FALSE;
}
