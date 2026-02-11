wep_entry_filter_cb (GtkEntry *   entry,
                     const gchar *text,
                     gint         length,
                     gint *       position,
                     gpointer     data)
{
	WirelessSecurityWEPKey *sec = (WirelessSecurityWEPKey *) data;
	GtkEditable *editable = GTK_EDITABLE (entry);
	int i, count = 0;
	gchar *result;

	result = g_malloc0 (length + 1);

	if (sec->type == NM_WEP_KEY_TYPE_KEY) {
		for (i = 0; i < length; i++) {
			if (isxdigit(text[i]) || isascii(text[i]))
				result[count++] = text[i];
		}
	} else if (sec->type == NM_WEP_KEY_TYPE_PASSPHRASE) {
		for (i = 0; i < length; i++)
			result[count++] = text[i];
	}

	if (count > 0) {
		g_signal_handlers_block_by_func (G_OBJECT (editable),
			                             G_CALLBACK (wep_entry_filter_cb),
			                             data);
		gtk_editable_insert_text (editable, result, count, position);
		g_signal_handlers_unblock_by_func (G_OBJECT (editable),
			                               G_CALLBACK (wep_entry_filter_cb),
			                               data);
	}

	g_signal_stop_emission_by_name (G_OBJECT (editable), "insert-text");
	g_free (result);
}
