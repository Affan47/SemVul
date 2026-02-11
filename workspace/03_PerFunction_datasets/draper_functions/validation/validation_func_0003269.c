config_comment(const char *s)
{
	const char *word;
	size_t line_len;
	str_t *out;

	g_assert(s != NULL);

	out = str_new(0);
	word = skip_ascii_spaces(s);
	line_len = 0;

	while ('\0' != word[0]) {
		static const size_t max_len = 72;
		const char *endptr;
		size_t word_len;

		endptr = skip_ascii_non_spaces(word);
		word_len = endptr - word;
		if (line_len >= max_len || word_len >= max_len - line_len) {
			if (line_len > 0)
				str_putc(out, '\n');
			line_len = 0;
		}
		if (0 == line_len) {
			str_putc(out, '#');
			line_len++;
		}

		str_putc(out, ' ');
		line_len++;
		str_cat_len(out, word, word_len);
		line_len += word_len;
		word = skip_ascii_spaces(endptr);
	}

	return str_s2c_null(&out);
}
