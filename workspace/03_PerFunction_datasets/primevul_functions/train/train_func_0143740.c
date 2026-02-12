static void conv_unreadable_8bit(gchar *str)
{
	register guchar *p = str;

	while (*p != '\0') {

		if (*p == '\r' && *(p + 1) == '\n')
			memmove(p, p + 1, strlen(p));
		else if (!IS_ASCII(*p)) *p = SUBST_CHAR;
		p++;
	}
}
