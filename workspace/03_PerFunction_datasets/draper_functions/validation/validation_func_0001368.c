parser_scan_mime_part_content (GMimeParser *parser, GMimePart *mime_part, int *found)
{
	struct _GMimeParserPrivate *priv = parser->priv;
	GMimeContentEncoding encoding;
	GByteArray *content = NULL;
	GMimeDataWrapper *wrapper;
	GMimeStream *stream;
	gint64 start, end;
	guint crlf;

	g_assert (priv->state >= GMIME_PARSER_STATE_HEADERS_END);

	if (priv->persist_stream && priv->seekable)
		start = parser_offset (priv, NULL);
	else
		content = g_byte_array_new ();

	*found = parser_scan_content (parser, content, &crlf);
	if (*found != FOUND_EOS) {

		if (priv->persist_stream && priv->seekable)
			end = parser_offset (priv, NULL) - crlf;
		else if (content->len > crlf)
			g_byte_array_set_size (content, content->len - crlf);
		else
			g_byte_array_set_size (content, 0);
	} else if (priv->persist_stream && priv->seekable) {
		end = parser_offset (priv, NULL);
	}

	encoding = g_mime_part_get_content_encoding (mime_part);

	if (priv->persist_stream && priv->seekable)
		stream = g_mime_stream_substream (priv->stream, start, end);
	else
		stream = g_mime_stream_mem_new_with_byte_array (content);

	wrapper = g_mime_data_wrapper_new_with_stream (stream, encoding);
	g_mime_part_set_content_object (mime_part, wrapper);
	g_object_unref (wrapper);
	g_object_unref (stream);
}
