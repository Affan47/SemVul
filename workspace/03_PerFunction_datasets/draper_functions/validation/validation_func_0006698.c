history_list_item_change(const gchar *key, const gchar *oldpath, const gchar *newpath)
{
	HistoryData *hd;
	GList *work;

	if (!oldpath) return;
	hd = history_list_find_by_key(key);
	if (!hd) return;

	work = hd->list;
	while (work)
		{
		gchar *buf = work->data;
		if (strcmp(buf, oldpath) == 0)
			{
			if (newpath)
				{
				work->data = g_strdup(newpath);
				}
			else
				{
				hd->list = g_list_remove(hd->list, buf);
				}
			g_free(buf);
			return;
			}
		work = work->next;
		}
}
