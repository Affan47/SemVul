file_browser_node_set_name (FileBrowserNode *node)
{
	g_free (node->name);
	g_free (node->markup);

	if (node->file)
		node->name = gedit_file_browser_utils_file_basename (node->file);
	else
		node->name = NULL;

	if (node->name)
		node->markup = g_markup_escape_text (node->name, -1);
	else
		node->markup = NULL;
}
