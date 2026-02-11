ui_set_fullscreen(void)
{
	if (ui_prefs.fullscreen)
	{
		gtk_window_fullscreen(GTK_WINDOW(main_widgets.window));
	}
	else
	{
		gtk_window_unfullscreen(GTK_WINDOW(main_widgets.window));
	}
}
