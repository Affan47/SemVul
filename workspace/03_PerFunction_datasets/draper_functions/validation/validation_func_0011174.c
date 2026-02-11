genius_display_error (GtkWidget *parent, const char *err)
{
	static GtkWidget *w = NULL;

	if (w != NULL)
		gtk_widget_destroy (w);

	if (parent == NULL)
		parent = genius_window;

	w = gtk_message_dialog_new (parent ?
				    GTK_WINDOW (parent) :
				    NULL ,
				    GTK_DIALOG_MODAL ,
				    GTK_MESSAGE_ERROR,
				    GTK_BUTTONS_CLOSE,
				    NULL);
	gtk_message_dialog_set_markup (GTK_MESSAGE_DIALOG (w), err);

	g_signal_connect (G_OBJECT (w), "destroy",
			  G_CALLBACK (gtk_widget_destroyed),
			  &w);

	gtk_dialog_run (GTK_DIALOG (w));
	gtk_widget_destroy (w);
}
