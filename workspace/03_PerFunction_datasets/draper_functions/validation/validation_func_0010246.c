enumerator_data_process (EnumeratorData *ed)
{
	TrackerCrawler *crawler;
	GSList *l;
	GList *children = NULL;
	gboolean use;

	crawler = ed->crawler;

	for (l = ed->dir_info->children; l; l = l->next) {
		DirectoryChildData *child_data;

		child_data = l->data;
		children = g_list_prepend (children, child_data->child);
	}

	g_signal_emit (crawler, signals[CHECK_DIRECTORY_CONTENTS], 0, ed->dir_info->node->data, children, &use);
	g_list_free (children);

	if (!use) {
		ed->dir_info->ignored_by_content = TRUE;

		return;
	}
}
