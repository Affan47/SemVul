totem_pl_parser_parse_date (const char *date_str, gboolean debug)
{
#ifdef HAVE_GMIME
	GTimeVal val;

	g_return_val_if_fail (date_str != NULL, -1);

	memset (&val, 0, sizeof(val));

	if (g_time_val_from_iso8601 (date_str, &val) != FALSE) {
		D(g_message ("Parsed duration '%s' using the ISO8601 parser", date_str));
		return val.tv_sec;
	}
	D(g_message ("Failed to parse duration '%s' using the ISO8601 parser", date_str));

	return g_mime_utils_header_decode_date (date_str, NULL);
#else
	WARN_NO_GMIME;
#endif
}
