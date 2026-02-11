panel_run_dialog_new (GdkScreen  *screen,
		      GtkBuilder *gui,
		      guint32    activate_time)
{
	PanelRunDialog *dialog;

	dialog = g_new0 (PanelRunDialog, 1);

	dialog->run_dialog = PANEL_GTK_BUILDER_GET (gui, "panel_run_dialog");

	dialog->run_settings = g_settings_new (PANEL_RUN_SCHEMA);

	g_signal_connect_swapped (dialog->run_dialog, "response",
				  G_CALLBACK (panel_run_dialog_response), dialog);

	g_signal_connect_swapped (dialog->run_dialog, "destroy",
				  G_CALLBACK (panel_run_dialog_destroy), dialog);

	dialog->run_button = PANEL_GTK_BUILDER_GET (gui, "run_button");
	dialog->terminal_checkbox = PANEL_GTK_BUILDER_GET (gui, "terminal_checkbox");

	panel_run_dialog_setup_pixmap        (dialog, gui);
	panel_run_dialog_setup_entry         (dialog, gui);
	panel_run_dialog_setup_file_button   (dialog, gui);
	panel_run_dialog_setup_program_list  (dialog, gui);
	panel_run_dialog_setup_list_expander (dialog, gui);

	gtk_window_set_icon_name (GTK_WINDOW (dialog->run_dialog),
				  PANEL_ICON_RUN);
	panel_run_dialog_set_default_icon (dialog, FALSE);

	g_signal_connect (dialog->run_settings, "changed::"PANEL_RUN_ENABLE_LIST_KEY,
			  G_CALLBACK (panel_run_dialog_update_program_list), dialog);
	g_signal_connect (dialog->run_settings, "changed::"PANEL_RUN_SHOW_LIST_KEY,
			  G_CALLBACK (panel_run_dialog_update_program_list), dialog);

	panel_run_dialog_update_program_list (dialog->run_settings, NULL, dialog);

	gtk_widget_set_sensitive (dialog->run_button, FALSE);

	gtk_dialog_set_default_response (GTK_DIALOG (dialog->run_dialog),
					 GTK_RESPONSE_OK);

	gtk_window_set_screen (GTK_WINDOW (dialog->run_dialog), screen);

	gtk_widget_grab_focus (dialog->combobox);
	gtk_widget_realize (dialog->run_dialog);
	gdk_x11_window_set_user_time (gtk_widget_get_window (dialog->run_dialog),
				      activate_time);
	gtk_widget_show (dialog->run_dialog);

	return dialog;
}
