update_global_smb_config (GstTool       *tool,
			  OobsSMBConfig *config)
{
	GtkWidget *widget;
	const gchar *str;
	gboolean is_wins_server;

	str = oobs_smb_config_get_workgroup (config);
	widget = gst_dialog_get_widget (tool->main_dialog, "smb_workgroup");
	gtk_entry_set_text (GTK_ENTRY (widget), (str) ? str : "");

	is_wins_server = oobs_smb_config_get_is_wins_server (config);
	widget = gst_dialog_get_widget (tool->main_dialog, "smb_is_wins");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), is_wins_server);

	str = oobs_smb_config_get_wins_server (config);
	widget = gst_dialog_get_widget (tool->main_dialog, "smb_wins_server");
	gtk_entry_set_text (GTK_ENTRY (widget), (str) ? str : "");
}
