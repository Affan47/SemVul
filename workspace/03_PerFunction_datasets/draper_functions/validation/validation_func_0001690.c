regex_search_fetch_match (GMatchInfo  *match_info,
			  const gchar *subject,
			  gssize       subject_length,
			  GtkTextIter *iter,
			  gint        *iter_byte_pos,
			  GtkTextIter *match_start,
			  GtkTextIter *match_end)
{
	gint start_byte_pos;
	gint end_byte_pos;
	gint nb_chars;

	g_assert (*iter_byte_pos <= subject_length);
	g_assert (match_start != NULL);
	g_assert (match_end != NULL);

	if (!g_match_info_matches (match_info))
	{
		return FALSE;
	}

	if (!g_match_info_fetch_pos (match_info, 0, &start_byte_pos, &end_byte_pos))
	{
		g_warning ("Impossible to fetch regex match position.");
		return FALSE;
	}

	g_assert (start_byte_pos < subject_length);
	g_assert (end_byte_pos <= subject_length);
	g_assert (*iter_byte_pos <= start_byte_pos);
	g_assert (start_byte_pos < end_byte_pos);

	nb_chars = g_utf8_strlen (subject + *iter_byte_pos,
				  start_byte_pos - *iter_byte_pos);

	*match_start = *iter;
	gtk_text_iter_forward_chars (match_start, nb_chars);

	nb_chars = g_utf8_strlen (subject + start_byte_pos,
				  end_byte_pos - start_byte_pos);

	*match_end = *match_start;
	gtk_text_iter_forward_chars (match_end, nb_chars);

	*iter = *match_end;
	*iter_byte_pos = end_byte_pos;

	return TRUE;
}
