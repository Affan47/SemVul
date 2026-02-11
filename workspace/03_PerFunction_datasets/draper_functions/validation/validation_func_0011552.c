do_fields_config_dialog (ETableConfig *config)
{
	GtkWidget *dialog;
	GtkWidget *content_area;
	GtkWidget *selector;
	GtkWidget *label;
	gint response, running = 1;

	dialog = gtk_dialog_new_with_buttons (
		_("Show Fields"),
		GTK_WINDOW (config->dialog_toplevel),
		0,
		GTK_STOCK_CANCEL,
		GTK_RESPONSE_CANCEL,
		GTK_STOCK_OK,
		GTK_RESPONSE_OK,
		NULL);

	gtk_container_set_border_width (GTK_CONTAINER (dialog), 5);
	gtk_window_set_default_size (GTK_WINDOW (dialog), 300, 400);

	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	gtk_box_set_spacing (GTK_BOX (content_area), 6);

	label = gtk_label_new (
		_("Choose the order of information "
		"to appear in the message list."));
	gtk_box_pack_start (GTK_BOX (content_area), label, FALSE, FALSE, 0);
	gtk_widget_show (label);

	selector = e_table_column_selector_new (config->state);
	gtk_container_set_border_width (GTK_CONTAINER (selector), 5);
	gtk_box_pack_start (GTK_BOX (content_area), selector, TRUE, TRUE, 0);
	gtk_widget_show (selector);

	do {
		response = gtk_dialog_run (GTK_DIALOG (dialog));
		switch (response) {
		case GTK_RESPONSE_OK:
			e_table_column_selector_apply (
				E_TABLE_COLUMN_SELECTOR (selector));
			running = 0;
			config_dialog_changed (config);
			break;

		case GTK_RESPONSE_DELETE_EVENT:
		case GTK_RESPONSE_CANCEL:
			running = 0;
			break;
		}

	} while (running);

	gtk_widget_destroy (dialog);

	config_fields_info_update (config);
}
