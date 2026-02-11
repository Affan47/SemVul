append_uri_encoded (GString *str, const char *in, const char *extra_enc_chars)
{
	const unsigned char *s = (const unsigned char *)in;

	while (*s) {
		if (soup_char_is_uri_percent_encoded (*s) ||
		    soup_char_is_uri_gen_delims (*s) ||
		    (extra_enc_chars && strchr (extra_enc_chars, *s)))
			g_string_append_printf (str, "%%%02X", (int)*s++);
		else
			g_string_append_c (str, *s++);
	}
}
