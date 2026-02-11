set_statusbar
	(
	char *name,
	int context,
	char *msg
	)
	{
	GtkWidget *sbar = glade_xml_get_widget(app_xml, name);
	if (sbar)
		return gtk_statusbar_push(GTK_STATUSBAR(sbar), context, msg);
	else
		return 0;
	}
