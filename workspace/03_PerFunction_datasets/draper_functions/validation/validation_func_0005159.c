action_changed (GeditFileChooserDialog *dialog,
		GParamSpec	       *pspec,
		gpointer		data)
{
	GtkFileChooserAction action;

	action = gtk_file_chooser_get_action (GTK_FILE_CHOOSER (dialog));

	switch (action)
	{
		case GTK_FILE_CHOOSER_ACTION_OPEN:
			g_object_set (dialog->priv->option_menu,
				      "save_mode", FALSE,
				      NULL);
			gtk_widget_show (dialog->priv->option_menu);
			break;
		case GTK_FILE_CHOOSER_ACTION_SAVE:
			g_object_set (dialog->priv->option_menu,
				      "save_mode", TRUE,
				      NULL);
			gtk_widget_show (dialog->priv->option_menu);
			break;
		default:
			gtk_widget_hide (dialog->priv->option_menu);
	}

	update_newline_visibility (dialog);
}
