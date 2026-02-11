gth_thumbnail_view_selection_changed_cb (GtkIconView *iconview,
					 gpointer     user_data)
{
	GthBrowser *browser = user_data;
	int         n_selected;

	if (gth_window_get_current_page (GTH_WINDOW (browser)) != GTH_BROWSER_PAGE_VIEWER)
		return;

	n_selected = gth_file_selection_get_n_selected (GTH_FILE_SELECTION (gth_browser_get_thumbnail_list_view (browser)));
	if (n_selected == 1) {
		GList       *items;
		GList       *file_list;
		GthFileData *selected_file_data;

		items = gth_file_selection_get_selected (GTH_FILE_SELECTION (gth_browser_get_thumbnail_list_view (browser)));
		file_list = gth_file_list_get_files (GTH_FILE_LIST (gth_browser_get_file_list (browser)), items);
		selected_file_data = (GthFileData *) file_list->data;
		gth_browser_load_file (browser, selected_file_data, FALSE);

		_g_object_list_unref (file_list);
		_gtk_tree_path_list_free (items);
	}
}
