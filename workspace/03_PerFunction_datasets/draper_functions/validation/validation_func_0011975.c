show_menu_popup(GtkUIManager *manager, guint button, guint32 time)
{
	GtkWidget *menu = gtk_ui_manager_get_widget (manager, "/MenuHBonds");
	if (GTK_IS_MENU (menu))
	{
		set_sensitive_option(manager,"/MenuHBonds/DeleteAtom");
		gtk_menu_popup (GTK_MENU (menu), NULL, NULL, NULL, NULL, button, time);
		return TRUE;
	}
	return FALSE;
}
