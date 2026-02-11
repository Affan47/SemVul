insert_closing_tag(GeanyEditor *editor, gint pos, gchar ch, const gchar *tag_name)
{
	ScintillaObject *sci = editor->sci;
	gchar *to_insert = NULL;

	if (ch == '/')
	{
		const gchar *gt = ">";

		if (sci_get_char_at(sci, pos) == '>')
			gt = "";

		to_insert = g_strconcat(tag_name, gt, NULL);
	}
	else
		to_insert = g_strconcat("</", tag_name, ">", NULL);

	sci_start_undo_action(sci);
	sci_replace_sel(sci, to_insert);
	if (ch == '>')
		sci_set_selection(sci, pos, pos);
	sci_end_undo_action(sci);
	g_free(to_insert);
}
