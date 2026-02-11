setup_create_pages (GtkWidget *box)
{
	GtkWidget *book;

	book = gtk_notebook_new ();

	setup_add_page (cata[1], book, setup_create_page (appearance_settings));
	setup_add_page (cata[2], book, setup_create_page (inputbox_settings));
	setup_add_page (cata[3], book, setup_create_page (userlist_settings));
	setup_add_page (cata[4], book, setup_create_page (tabs_settings));
	setup_add_page (cata[5], book, setup_create_color_page ());

	setup_add_page (cata[8], book, setup_create_page (general_settings));

	if (unity_mode ())
	{
		setup_add_page (cata[9], book, setup_create_page (alert_settings_unity));
	}
	else
	{
		setup_add_page (cata[9], book, setup_create_page (alert_settings));
	}

	setup_add_page (cata[10], book, setup_create_sound_page ());
	setup_add_page (cata[11], book, setup_create_page (logging_settings));
	setup_add_page (cata[12], book, setup_create_page (advanced_settings));

	setup_add_page (cata[14], book, setup_create_page (network_settings));
	setup_add_page (cata[15], book, setup_create_page (filexfer_settings));

	gtk_notebook_set_show_tabs (GTK_NOTEBOOK (book), FALSE);
	gtk_notebook_set_show_border (GTK_NOTEBOOK (book), FALSE);
	gtk_container_add (GTK_CONTAINER (box), book);

	return book;
}
