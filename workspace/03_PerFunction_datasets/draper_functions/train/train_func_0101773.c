camel_header_address_fold (const gchar *in,
                           gsize headerlen)
{
	gsize len, outlen;
	const gchar *inptr = in, *space, *p, *n;
	GString *out;
	gchar *ret;
	gint i, needunfold = FALSE;

	if (in == NULL)
		return NULL;


	len = headerlen + 2;
	p = in;
	while (*p) {
		n = strchr (p, '\n');
		if (n == NULL) {
			len += strlen (p);
			break;
		}

		needunfold = TRUE;
		len += n - p;

		if (len >= CAMEL_FOLD_SIZE)
			break;
		len = 0;
		p = n + 1;
	}
	if (len < CAMEL_FOLD_SIZE)
		return g_strdup (in);


	if (needunfold)
		inptr = in = camel_header_unfold (in);

	out = g_string_new ("");
	outlen = headerlen + 2;
	while (*inptr) {
		space = strchr (inptr, ' ');
		if (space) {
			len = space - inptr + 1;
		} else {
			len = strlen (inptr);
		}

		d (printf ("next word '%.*s'\n", len, inptr));

		if (outlen + len > CAMEL_FOLD_SIZE) {
			d (printf ("outlen = %d wordlen = %d\n", outlen, len));

			if (out->len > 0 && out->str[out->len - 1] == ' ')
				g_string_truncate (out, out->len - 1);
			g_string_append (out, "\n\t");
			outlen = 1;
		}

		outlen += len;
		for (i = 0; i < len; i++) {
			g_string_append_c (out, inptr[i]);
		}

		inptr += len;
	}
	ret = out->str;
	g_string_free (out, FALSE);

	if (needunfold)
		g_free ((gchar *) in);

	return ret;
}
