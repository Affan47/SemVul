dialog_search_replace_query (WBCGtk *wbcg,
			     GnmSearchReplace *sr,
			     const char *location,
			     const char *old_text,
			     const char *new_text)
{
	GtkBuilder *gui;
	GtkDialog *dialog;
	int res;

	g_return_val_if_fail (wbcg != NULL, 0);

	gui = gnm_gtk_builder_load ("search-replace.ui", NULL, GO_CMD_CONTEXT (wbcg));
        if (gui == NULL)
                return 0;

	dialog = GTK_DIALOG (go_gtk_builder_get_widget (gui, "query_dialog"));


	gtk_widget_destroy (go_gtk_builder_get_widget (gui, "search_replace_dialog"));

	gtk_entry_set_text (GTK_ENTRY (go_gtk_builder_get_widget (gui, "qd_location")),
			    location);
	gtk_entry_set_text (GTK_ENTRY (go_gtk_builder_get_widget (gui, "qd_old_text")),
			    old_text);
	gtk_entry_set_text (GTK_ENTRY (go_gtk_builder_get_widget (gui, "qd_new_text")),
			    new_text);

	set_checked (gui, "qd_query", sr->query);

	wbcg_set_transient (wbcg, GTK_WINDOW (dialog));
	go_dialog_guess_alternative_button_order (dialog);
	gtk_widget_show_all (GTK_WIDGET (dialog));

	gnm_dialog_setup_destroy_handlers (dialog, wbcg,
					   GNM_DIALOG_DESTROY_SHEET_REMOVED);

	res = gtk_dialog_run (dialog);
	switch (res) {
	case GTK_RESPONSE_YES:
	case GTK_RESPONSE_NO:
		sr->query = is_checked (gui, "qd_query");
		break;
	default:
		res = GTK_RESPONSE_CANCEL;
	}

	gtk_widget_destroy (GTK_WIDGET (dialog));
	g_object_unref (gui);

	return res;
}
