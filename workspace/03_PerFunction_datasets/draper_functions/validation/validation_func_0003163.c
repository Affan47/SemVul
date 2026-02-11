message_get_view_iter (GeditWindow    *window,
                       GeditMessage   *message,
                       GtkSourceView **view,
                       GtkTextIter    *iter)
{
	g_object_get (message, "view", view, NULL);
	if (!*view)
	{
		*view = GTK_SOURCE_VIEW (gedit_window_get_active_view (window));
	}

	if (!*view)
	{
		return;
	}

	g_object_get (message, "iter", iter, NULL);
	if (iter)
	{
		GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (*view));
		gtk_text_buffer_get_iter_at_mark (buffer,
		                                  iter,
		                                  gtk_text_buffer_get_insert (buffer));
	}
}
