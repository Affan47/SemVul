panel_run_dialog_append_file_utf8 (PanelRunDialog *dialog,
				   const char     *file)
{
	const char *text;
	char       *quoted, *temp;
	GtkWidget  *entry;


	if (!file || !file[0] || file[0] == '-')
		return;

	quoted = quote_string (file);
	entry = gtk_bin_get_child (GTK_BIN (dialog->combobox));
	text = gtk_entry_get_text (GTK_ENTRY (entry));
	if (text && text [0]) {
		temp = g_strconcat (text, " ", quoted, NULL);
		gtk_entry_set_text (GTK_ENTRY (entry), temp);
		g_free (temp);
	} else
		gtk_entry_set_text (GTK_ENTRY (entry), quoted);

	g_free (quoted);
}
