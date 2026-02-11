advance (char const **str, gboolean utf8)
{
	if (utf8) {
		gunichar c;

		c = g_utf8_get_char(*str);
		*str = g_utf8_next_char(*str);

		return unichar_isprint(c) ? mk_wcwidth(c) : 1;
	} else {
		*str += 1;

		return 1;
	}
}
