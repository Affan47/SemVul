on_window_state_event(GtkWidget *widget, GdkEventWindowState *event, gpointer user_data)
{

	if (event->changed_mask & GDK_WINDOW_STATE_FULLSCREEN)
	{
		static GtkWidget *menuitem = NULL;

		if (menuitem == NULL)
			menuitem = ui_lookup_widget(widget, "menu_fullscreen1");

		ignore_callback = TRUE;

		ui_prefs.fullscreen = (event->new_window_state & GDK_WINDOW_STATE_FULLSCREEN) ? TRUE : FALSE;
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menuitem), ui_prefs.fullscreen);

		ignore_callback = FALSE;
	}
	return FALSE;
}
