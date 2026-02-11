get_header_decoded (const gchar *header_value,
                    const gchar *default_charset)
{
	gchar *unfold, *decoded;

	if (!header_value || !*header_value)
		return NULL;

	unfold = camel_header_unfold (header_value);
	decoded = camel_header_decode_string (unfold, default_charset);
	g_free (unfold);

	return decoded;
}
