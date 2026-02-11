on_treeview_popup_menu  (GtkWidget *widget,
					 	ProjectManagerPlugin *plugin)
{
	AnjutaUI *ui;
	GtkWidget *popup;

	ui = anjuta_shell_get_ui (ANJUTA_PLUGIN (plugin)->shell, NULL);
	popup = gtk_ui_manager_get_widget (GTK_UI_MANAGER (ui), "/PopupProjectManager");
	g_return_val_if_fail (GTK_IS_WIDGET (popup), FALSE);

	gtk_menu_popup (GTK_MENU (popup),
					NULL, NULL, NULL, NULL,
					0,
					gtk_get_current_event_time());

	return TRUE;
}
