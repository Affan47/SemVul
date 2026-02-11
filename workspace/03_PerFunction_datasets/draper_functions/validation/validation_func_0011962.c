really_save_console_cb (GtkFileChooser *fs, int response, gpointer data)
{
	char *s;
	char *base;
	char *output;
	glong row, column;
	int sz;

	if (response != GTK_RESPONSE_OK) {
		gtk_widget_destroy (GTK_WIDGET (fs));

		gtk_widget_set_sensitive (genius_window, TRUE);
		return;
	}

	s = g_strdup (gtk_file_chooser_get_uri (fs));
	if (s == NULL)
		return;
	base = g_path_get_basename (s);
	if (base != NULL && base[0] != '\0' &&
	    strchr (base, '.') == NULL) {
		char *n = g_strconcat (s, ".gel", NULL);
		g_free (s);
		s = n;
	}
	g_free (base);


	vte_terminal_get_cursor_position (VTE_TERMINAL (term),
					  &column, &row);
	output = vte_terminal_get_text_range (VTE_TERMINAL (term),
					      MAX(row-genius_setup.scrollback+1, 0),
					      0,
					      row,
					      vte_terminal_get_column_count (VTE_TERMINAL (term)) - 1,
					      always_selected,
					      NULL,
					      NULL);
	sz = strlen (output);

	if ( ! save_contents_vfs (s, output, sz)) {
		char *err = g_strdup_printf (_("<b>Cannot save file</b>\n"
					       "Details: %s"),
					     g_strerror (errno));
		genius_display_error (GTK_WIDGET (fs), err);
		g_free (err);
		g_free (output);
		g_free (s);
		return;
	}
	g_free (output);

	g_free (last_dir);
	last_dir = gtk_file_chooser_get_current_folder (fs);

	gtk_widget_destroy (GTK_WIDGET (fs));

	gtk_widget_set_sensitive (genius_window, TRUE);

	g_free (s);
}
