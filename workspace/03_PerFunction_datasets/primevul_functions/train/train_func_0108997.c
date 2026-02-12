text_convert_invalid (const gchar* text, gssize len, GIConv converter, const gchar *fallback, gsize *len_out)
{
	gchar *result_part;
	gsize result_part_len;
	const gchar *end;
	gsize invalid_start_pos;
	GString *result;
	const gchar *current_start;

	if (len == -1)
	{
		len = strlen (text);
	}

	end = text + len;


	result_part = g_convert_with_iconv (text, len, converter, &invalid_start_pos, &result_part_len, NULL);
	g_iconv (converter, NULL, NULL, NULL, NULL);

	if (result_part != NULL)
	{


		if (len_out != NULL)
		{
			*len_out = result_part_len;
		}

		return result_part;
	}


	result = g_string_sized_new (len);
	current_start = text;

	for (;;)
	{
		g_assert (current_start + invalid_start_pos < end);


		result_part = g_convert_with_iconv (current_start, invalid_start_pos, converter, &invalid_start_pos, &result_part_len, NULL);
		g_iconv (converter, NULL, NULL, NULL, NULL);

		g_assert (result_part != NULL);
		g_string_append_len (result, result_part, result_part_len);
		g_free (result_part);


		g_string_append (result, fallback);


		current_start += invalid_start_pos + 1;

		result_part = g_convert_with_iconv (current_start, end - current_start, converter, &invalid_start_pos, &result_part_len, NULL);
		g_iconv (converter, NULL, NULL, NULL, NULL);

		if (result_part != NULL)
		{


			g_string_append_len (result, result_part, result_part_len);
			g_free (result_part);

			if (len_out != NULL)
			{
				*len_out = result->len;
			}

			return g_string_free (result, FALSE);
		}


	}
}
