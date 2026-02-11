rb_uri_dialog_text_changed (GtkEditable *buffer,
				    RBURIDialog *dialog)
{
	char *text = gtk_editable_get_chars (buffer, 0, -1);
	gboolean has_text = ((text != NULL) && (*text != 0));

	g_free (text);

	gtk_widget_set_sensitive (dialog->priv->okbutton, has_text);
}
