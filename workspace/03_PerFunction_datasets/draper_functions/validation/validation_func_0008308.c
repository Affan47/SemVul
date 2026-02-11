tds_convert_string(TDSSOCKET * tds, const TDSICONV * char_conv, const char *s, int len, size_t *out_len)
{
	char *buf;

	const char *ib;
	char *ob;
	size_t il, ol;


	TDS_ERRNO_MESSAGE_FLAGS *suppress = (TDS_ERRNO_MESSAGE_FLAGS*) &char_conv->suppress;

	CHECK_TDS_EXTRA(tds);

	il = len < 0 ? strlen(s) : len;
	if (char_conv->flags == TDS_ENCODING_MEMCPY) {
		*out_len = il;
		return s;
	}


	ol = il * char_conv->server_charset.max_bytes_per_char / char_conv->client_charset.min_bytes_per_char + 1;
	buf = (char *) malloc(ol);
	if (!buf)
		return NULL;

	ib = s;
	ob = buf;
	memset(suppress, 0, sizeof(char_conv->suppress));
	if (tds_iconv(tds, char_conv, to_server, &ib, &il, &ob, &ol) == (size_t)-1) {
		free(buf);
		return NULL;
	}
	*out_len = ob - buf;
	return buf;
}
