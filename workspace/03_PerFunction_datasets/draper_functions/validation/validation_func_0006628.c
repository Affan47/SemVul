on_open_failed (SourceviewIO* io, GError* err, Sourceview* sv)
{
	AnjutaShell* shell = ANJUTA_PLUGIN (sv->priv->plugin)->shell;
	IAnjutaDocumentManager *docman =
		anjuta_shell_get_interface (shell, IAnjutaDocumentManager, NULL);
	g_return_if_fail (docman != NULL);
	GList* documents = ianjuta_document_manager_get_doc_widgets (docman, NULL);
	GtkWidget* message_area;


	gchar* message = g_strdup_printf (_("Could not open %s: %s"),
									  sourceview_io_get_filename (sv->priv->io),
									  err->message);

	if (g_list_find (documents, sv))
	{
		message_area = anjuta_message_area_new (message, GTK_MESSAGE_WARNING);
		gtk_info_bar_add_button (GTK_INFO_BAR (message_area),
										GTK_STOCK_OK,
										GTK_RESPONSE_OK);
		g_signal_connect (message_area, "response", G_CALLBACK(message_area_destroy), NULL);

		sourceview_set_message_area (sv, message_area);
	}
	else
	{
		GtkWidget* dialog = gtk_message_dialog_new (NULL, 0,
													GTK_MESSAGE_ERROR,
													GTK_BUTTONS_OK,
													"%s", message);
		g_signal_connect (dialog, "response", G_CALLBACK(gtk_widget_destroy), NULL);
		gtk_dialog_run (GTK_DIALOG (dialog));
	}
	g_free (message);
	sv->priv->loading = FALSE;
	gtk_text_view_set_editable (GTK_TEXT_VIEW (sv->priv->view), TRUE);
}
