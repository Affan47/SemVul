imapx_server_check_is_broken_cyrus (const gchar *response_text,
				    gboolean *inout_is_cyrus)
{
	const gchar *pp, *from;
	gint vermajor = 0, verminor = 0, vermicro = 0;

	g_return_val_if_fail (inout_is_cyrus != NULL, FALSE);


	if (*inout_is_cyrus)
		return FALSE;

	if (!response_text || !*response_text)
		return FALSE;


	pp = response_text;
	while (pp = camel_strstrcase (pp, "cyrus"), pp) {

		if ((pp == response_text || g_ascii_isspace (pp[-1])) && g_ascii_isspace (pp[5]))
			break;
		pp++;
	}

	if (!pp)
		return FALSE;

	from = pp;


	while (pp = from, pp && *pp) {
		#define skip_word() \
			while (*pp && *pp != ' ') {	\
				pp++;			\
			}				\
							\
			if (!*pp)			\
				return TRUE;		\
							\
			pp++;


		skip_word ();


		skip_word ();

		#undef skip_word


		if (*pp == 'v')
			pp++;

		if (sscanf (pp, "%d.%d.%d", &vermajor, &verminor, &vermicro) == 3) {
			*inout_is_cyrus = TRUE;
			break;
		}

		vermajor = 0;

		pp = from + 1;
		from = NULL;

		while (pp = camel_strstrcase (pp, "cyrus"), pp) {

			if (g_ascii_isspace (pp[-1]) && g_ascii_isspace (pp[5])) {
				from = pp;
				break;
			}

			pp++;
		}
	}


	return !(vermajor > 2 || (vermajor == 2 && (verminor > 5 || (verminor == 5 && vermicro >= 11))));
}
