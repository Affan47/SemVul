ImportSpeedDial(void)
{
	static GtkWidget *fileDialog = NULL;

	if (fileDialog == NULL) {
		fileDialog = gtk_file_selection_new(_("Import from file"));
		gtk_signal_connect(GTK_OBJECT(fileDialog), "delete_event",
				   GTK_SIGNAL_FUNC(DeleteEvent), NULL);
		gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fileDialog)->ok_button),
				   "clicked", GTK_SIGNAL_FUNC(OkImportDialog),
				   (gpointer) fileDialog);
		gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fileDialog)->cancel_button),
				   "clicked", GTK_SIGNAL_FUNC(CancelDialog), (gpointer) fileDialog);
	}

	gtk_widget_show(fileDialog);
}
