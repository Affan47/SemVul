entry_event (GtkEditable    *entry,
	     GdkEventKey    *event,
	     PanelRunDialog *dialog)
{
	GtkTreeSelection *selection;
	char             *prefix;
	char             *nospace_prefix;
	char             *nprefix;
	char             *temp;
	int               pos, tmp;

	if (event->type != GDK_KEY_PRESS)
		return FALSE;


	dialog->use_program_list = FALSE;
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (dialog->program_list));
	gtk_tree_selection_unselect_all (selection);

	if (!g_settings_get_boolean (dialog->run_settings,
				     PANEL_RUN_ENABLE_COMPLETION_KEY))
		return FALSE;


	if (event->keyval == GDK_KEY_Tab) {
		gtk_editable_get_selection_bounds (entry, &pos, &tmp);

		if (dialog->completion_started &&
		    pos != tmp &&
		    pos != 1 &&
		    tmp == strlen (gtk_entry_get_text (GTK_ENTRY (entry)))) {
	    		gtk_editable_select_region (entry, 0, 0);
			gtk_editable_set_position (entry, -1);

			return TRUE;
		}
	} else if (event->length > 0) {

		gtk_editable_get_selection_bounds (entry, &pos, &tmp);

		if (dialog->completion_started &&
		    pos != tmp &&
		    pos != 0 &&
		    tmp == strlen (gtk_entry_get_text (GTK_ENTRY (entry)))) {
			temp = gtk_editable_get_chars (entry, 0, pos);
			prefix = g_strconcat (temp, event->string, NULL);
			g_free (temp);
		} else if (pos == tmp &&
			   tmp == strlen (gtk_entry_get_text (GTK_ENTRY (entry)))) {
			prefix = g_strconcat (gtk_entry_get_text (GTK_ENTRY (entry)),
					      event->string, NULL);
		} else {
			return FALSE;
		}

		nospace_prefix = prefix;
		while (*nospace_prefix != '\0' &&
		       g_ascii_isspace (*nospace_prefix))
			nospace_prefix++;
		if (*nospace_prefix == '\0')
			return FALSE;

		panel_run_dialog_update_completion (dialog, nospace_prefix);

		if (!dialog->completion) {
			g_free (prefix);
			return FALSE;
		}

		pos = strlen (prefix);
		nprefix = NULL;

		g_completion_complete_utf8 (dialog->completion, nospace_prefix,
					    &nprefix);

		if (nprefix) {
			int insertpos;
			insertpos = 0;

			temp = g_strndup (prefix, nospace_prefix - prefix);
			g_free (prefix);

			prefix = g_strconcat (temp, nprefix, NULL);

			g_signal_handler_block (dialog->combobox,
						dialog->changed_id);
			gtk_editable_delete_text (entry, 0, -1);
			g_signal_handler_unblock (dialog->combobox,
						  dialog->changed_id);

			gtk_editable_insert_text (entry,
						  prefix, strlen (prefix),
						  &insertpos);

 			gtk_editable_set_position (entry, pos);
			gtk_editable_select_region (entry, pos, -1);

			dialog->completion_started = TRUE;

			g_free (temp);
			g_free (nprefix);
			g_free (prefix);

			return TRUE;
		}

		g_free (prefix);
	}

	return FALSE;
}
