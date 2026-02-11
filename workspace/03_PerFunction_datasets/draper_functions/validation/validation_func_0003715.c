et_get_text_after_offset (AtkText *text,
                          gint offset,
                          AtkTextBoundary boundary_type,
                          gint *start_offset,
                          gint *end_offset)
{
	gint start, end, len;
	const gchar *full_text = et_get_full_text (text);
	g_return_val_if_fail (full_text, NULL);

	switch (boundary_type)
	{
	case ATK_TEXT_BOUNDARY_CHAR:
		start = offset + 1;
		end = offset + 2;
		break;
	case ATK_TEXT_BOUNDARY_WORD_START:
		start = find_word_start (full_text, offset + 1, 1);
		end = find_word_start (full_text, start + 1, 1);
		break;
	case ATK_TEXT_BOUNDARY_WORD_END:
		start = find_word_end (full_text, offset + 1, 1);
		end = find_word_end (full_text, start + 1, 1);
		break;
	case ATK_TEXT_BOUNDARY_SENTENCE_START:
		start = find_sentence_start (full_text, offset + 1, 1);
		end = find_sentence_start (full_text, start + 1, 1);
		break;
	case ATK_TEXT_BOUNDARY_SENTENCE_END:
		start = find_sentence_end (full_text, offset + 1, 1);
		end = find_sentence_end (full_text, start + 1, 1);
		break;
	case ATK_TEXT_BOUNDARY_LINE_START:
		start = find_line_start (full_text, offset + 1, 1);
		end = find_line_start (full_text, start + 1, 1);
		break;
	case ATK_TEXT_BOUNDARY_LINE_END:
		start = find_line_end (full_text, offset + 1, 1);
		end = find_line_end (full_text, start + 1, 1);
		break;
	default:
		return NULL;
	}

	len = g_utf8_strlen (full_text, -1);
	if (start_offset)
		*start_offset = MIN (MAX (0, start), len);
	if (end_offset)
		*end_offset = MIN (MAX (0, end), len);
	return et_get_text (text, start, end);
}
