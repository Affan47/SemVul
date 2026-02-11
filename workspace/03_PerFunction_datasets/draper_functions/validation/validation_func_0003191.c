soup_body_output_stream_write_raw (SoupBodyOutputStream  *bostream,
				   const void            *buffer,
				   gsize                  count,
				   gboolean               blocking,
				   GCancellable          *cancellable,
				   GError               **error)
{
	gssize nwrote, my_count;


	if (bostream->priv->write_length) {
		my_count = MIN (count, bostream->priv->write_length - bostream->priv->written);
		if (my_count == 0) {
			bostream->priv->eof = TRUE;
			return count;
		}
	} else
		my_count = count;

	nwrote = g_pollable_stream_write (bostream->priv->base_stream,
					  buffer, my_count,
					  blocking, cancellable, error);

	if (nwrote > 0 && bostream->priv->write_length)
		bostream->priv->written += nwrote;

	if (nwrote == my_count && my_count != count)
		nwrote = count;

	return nwrote;
}
