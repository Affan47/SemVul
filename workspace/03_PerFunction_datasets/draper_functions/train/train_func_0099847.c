sc_speller_process_line(GeanyDocument *doc, gint line_number, const gchar *line)
{
	gint pos_start, pos_end;
	gint wstart, wend;
	GString *str;
	gint suggestions_found = 0;
	gchar c;

	g_return_val_if_fail(sc_speller_dict != NULL, 0);
	g_return_val_if_fail(doc != NULL, 0);
	g_return_val_if_fail(line != NULL, 0);

	str = g_string_sized_new(256);

	pos_start = sci_get_position_from_line(doc->editor->sci, line_number);
	pos_end = sci_get_position_from_line(doc->editor->sci, line_number + 1);

	while (pos_start < pos_end)
	{
		wstart = scintilla_send_message(doc->editor->sci, SCI_WORDSTARTPOSITION, pos_start, TRUE);
		wend = scintilla_send_message(doc->editor->sci, SCI_WORDENDPOSITION, wstart, FALSE);
		if (wstart == wend)
			break;
		c = sci_get_char_at(doc->editor->sci, wstart);

		if (ispunct(c) || isspace(c))
		{
			pos_start++;
			continue;
		}


		if (str->len < (guint)(wend - wstart))
			g_string_set_size(str, wend - wstart);

		sci_get_text_range(doc->editor->sci, wstart, wend, str->str);

		suggestions_found += sc_speller_check_word(doc, line_number, str->str, wstart, wend);

		pos_start = wend + 1;
	}

	g_string_free(str, TRUE);
	return suggestions_found;
}
