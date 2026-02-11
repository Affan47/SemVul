gth_browser_activate_action_edit_rename (GtkAction  *action,
					 GthBrowser *browser)
{
	GtkWidget *folder_tree;
	GtkWidget *file_list;

	folder_tree = gth_browser_get_folder_tree (browser);
	if (gtk_widget_has_focus (folder_tree)) {
		GthFileData *file_data;

		file_data = gth_folder_tree_get_selected (GTH_FOLDER_TREE (folder_tree));
		if ((file_data != NULL) && g_file_info_get_attribute_boolean (file_data->info, G_FILE_ATTRIBUTE_ACCESS_CAN_RENAME))
			gth_folder_tree_start_editing (GTH_FOLDER_TREE (folder_tree), file_data->file);

		_g_object_unref (file_data);

		return;
	}

	file_list = gth_browser_get_file_list_view (browser);
	if (gtk_widget_has_focus (file_list)) {
		gth_hook_invoke ("gth-browser-file-list-rename", browser);
		return;
	}

	if (gth_window_get_current_page (GTH_WINDOW (browser)) == GTH_BROWSER_PAGE_VIEWER) {
		gth_hook_invoke ("gth-browser-file-list-rename", browser);
		return;
	}
}
