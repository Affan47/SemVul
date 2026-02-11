soup_body_input_stream_read_chunked (SoupBodyInputStream  *bistream,
				     void                 *buffer,
				     gsize                 count,
				     gboolean              blocking,
				     GCancellable         *cancellable,
				     GError              **error)
{
	SoupFilterInputStream *fstream = SOUP_FILTER_INPUT_STREAM (bistream->priv->base_stream);
	char metabuf[128];
	gssize nread;
	gboolean got_line;

again:
	switch (bistream->priv->chunked_state) {
	case SOUP_BODY_INPUT_STREAM_STATE_CHUNK_SIZE:
		nread = soup_filter_input_stream_read_line (
			fstream, metabuf, sizeof (metabuf), blocking,
			&got_line, cancellable, error);
		if (nread <= 0)
			return nread;
		if (!got_line) {
			g_set_error_literal (error, G_IO_ERROR,
					     G_IO_ERROR_PARTIAL_INPUT,
					     _("Connection terminated unexpectedly"));
			return -1;
		}

		bistream->priv->read_length = strtoul (metabuf, NULL, 16);
		if (bistream->priv->read_length > 0)
			bistream->priv->chunked_state = SOUP_BODY_INPUT_STREAM_STATE_CHUNK;
		else
			bistream->priv->chunked_state = SOUP_BODY_INPUT_STREAM_STATE_TRAILERS;
		break;

	case SOUP_BODY_INPUT_STREAM_STATE_CHUNK:
		nread = soup_body_input_stream_read_raw (
			bistream, buffer,
			MIN (count, bistream->priv->read_length),
			blocking, cancellable, error);
		if (nread > 0) {
			bistream->priv->read_length -= nread;
			if (bistream->priv->read_length == 0)
				bistream->priv->chunked_state = SOUP_BODY_INPUT_STREAM_STATE_CHUNK_END;
		}
		return nread;

	case SOUP_BODY_INPUT_STREAM_STATE_CHUNK_END:
		nread = soup_filter_input_stream_read_line (
			SOUP_FILTER_INPUT_STREAM (bistream->priv->base_stream),
			metabuf, sizeof (metabuf), blocking,
			&got_line, cancellable, error);
		if (nread <= 0)
			return nread;
		if (!got_line) {
			g_set_error_literal (error, G_IO_ERROR,
					     G_IO_ERROR_PARTIAL_INPUT,
					     _("Connection terminated unexpectedly"));
			return -1;
		}

		bistream->priv->chunked_state = SOUP_BODY_INPUT_STREAM_STATE_CHUNK_SIZE;
		break;

	case SOUP_BODY_INPUT_STREAM_STATE_TRAILERS:
		nread = soup_filter_input_stream_read_line (
			fstream, buffer, count, blocking,
			&got_line, cancellable, error);
		if (nread <= 0)
			return nread;

		if (strncmp (buffer, "\r\n", nread) || strncmp (buffer, "\n", nread)) {
			bistream->priv->chunked_state = SOUP_BODY_INPUT_STREAM_STATE_DONE;
			bistream->priv->eof = TRUE;
		}
		break;

	case SOUP_BODY_INPUT_STREAM_STATE_DONE:
		return 0;
	}

	goto again;
}
