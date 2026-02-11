edit_metadata__gth_browser_update_sensitivity_cb (GthBrowser *browser)
{
	BrowserData *data;
	int          n_selected;
	gboolean     sensitive;

	data = g_object_get_data (G_OBJECT (browser), BROWSER_DATA_KEY);
	g_return_if_fail (data != NULL);

	n_selected = gth_file_selection_get_n_selected (GTH_FILE_SELECTION (gth_browser_get_file_list_view (browser)));

	sensitive = (n_selected > 0);
	g_object_set (gtk_action_group_get_action (data->actions, "Edit_Metadata"), "sensitive", sensitive, NULL);
	g_object_set (gtk_action_group_get_action (data->actions, "Tool_DeleteMetadata"), "sensitive", sensitive, NULL);
}
