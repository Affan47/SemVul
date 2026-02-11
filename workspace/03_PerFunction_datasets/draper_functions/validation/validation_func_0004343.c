ertf_read_line(ERTFParser *parser)
{
	gchar buf[ERTFBUFSIZE];
	gchar buf2[ERTFBUFSIZE];
	gint index;

	if (fgets(buf, sizeof(buf), parser->fp) == NULL) {
		parser->state = ERTF_EOF;
		return ERTF_EOF;
	}

	if (conv_convert(parser->conv, buf2, sizeof(buf2), buf) < 0) {
		g_warning("ertf_read_line(): code conversion failed\n");

		index = parser->bufp - parser->buf->str;

		g_string_append(parser->buf, buf);

		parser->bufp = parser->buf->str + index;

		return ERTF_ERR;
	}

	index = parser->bufp - parser->buf->str;

	g_string_append(parser->buf, buf2);

	parser->bufp = parser->buf->str + index;

	return ERTF_NORMAL;
}
