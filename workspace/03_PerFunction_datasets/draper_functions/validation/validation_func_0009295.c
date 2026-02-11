stop_animation(GtkWidget *win, gpointer data)
{
	play = FALSE;
	if(GTK_IS_WIDGET(PlayButton)) gtk_widget_set_sensitive(PlayButton, TRUE);

	if(GTK_IS_WIDGET(StopButton)) gtk_widget_set_sensitive(StopButton, FALSE);

	if(GTK_IS_WIDGET(WinDlg)) gtk_window_set_modal (GTK_WINDOW (WinDlg), FALSE);

	while( gtk_events_pending() )
		gtk_main_iteration();

	if(this_is_an_object((GtkObject*)GLArea))
		glarea_rafresh(GLArea);
	set_color_surface(0,colorP);
	set_color_surface(1,colorN);
	set_color_surface(2,colorD);
}
