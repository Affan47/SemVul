window_destroyed (GtkWidget *window,
		  gpointer data)
{
	windows = g_list_remove (windows, window);

	if (windows == NULL) {
		gtk_main_quit ();
	}
}
