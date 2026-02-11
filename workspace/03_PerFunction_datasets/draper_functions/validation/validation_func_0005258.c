gdb_info_show_string (GtkWindow *parent, const gchar *s,
					  gint width, gint height)
{
	GtkWidget *textview;
	GtkTextBuffer *buffer;

	g_return_val_if_fail (s != NULL, FALSE);

	textview = create_dialog_with_textview (parent,
											width, height);
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
	gtk_text_buffer_set_text (buffer, s, strlen (s));

	return TRUE;
}
