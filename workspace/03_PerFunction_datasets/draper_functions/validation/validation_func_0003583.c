shell_write_lines(struct gnutella_shell *sh, int code, const char *text)
{
	str_t *str;
	int c;
	const char *p = text;

	shell_check(sh);
	g_return_if_fail(text);

	str = str_new(0);

	while ((c = *p++)) {
		if ('\n' == c) {
			shell_pending_add(sh, code, str_2c(str));
			str_reset(str);
		} else {
			str_putc(str, c);
		}
	}

	if (0 != str_len(str))
		shell_pending_add(sh, code, str_2c(str));

	str_destroy_null(&str);
}
