readAGabeditDlg(GtkWidget* xyplot)
{
	GtkFileFilter *filter;
	GtkWidget *dialog;
	GtkWidget *parentWindow;

	dialog = g_object_new (GTK_TYPE_FILE_CHOOSER_DIALOG, "action", GTK_FILE_CHOOSER_ACTION_OPEN, "file-system-backend", "gtk+", "select-multiple", FALSE, NULL);
	gtk_window_set_title (GTK_WINDOW (dialog), _("Read a Gabedit file"));
	gtk_dialog_add_buttons (GTK_DIALOG (dialog), GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_OK, NULL);

	filter = gtk_file_filter_new ();

	gtk_file_filter_set_name (filter, "*.gab");
	gtk_file_filter_add_pattern (filter, "*.gab");
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (dialog), filter);

	gtk_dialog_set_default_response (GTK_DIALOG (dialog), GTK_RESPONSE_OK);
	g_signal_connect (dialog, "response",  G_CALLBACK (readAGabedit),GTK_OBJECT(dialog));
	g_signal_connect (dialog, "response", G_CALLBACK (gtk_widget_destroy),GTK_OBJECT(dialog));

	g_object_set_data (G_OBJECT (dialog), "XYPLOT",xyplot);
	gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
	parentWindow = get_parent_window(GTK_WIDGET(xyplot));
	if(parentWindow) gtk_window_set_transient_for(GTK_WINDOW(dialog),GTK_WINDOW(parentWindow));
	gtk_widget_show(dialog);
}
