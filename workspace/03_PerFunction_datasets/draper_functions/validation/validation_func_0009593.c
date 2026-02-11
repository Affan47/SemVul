soap_sax_characters (gpointer _ctxt,
                     const xmlChar *ch,
                     gint len)
{
	xmlParserCtxt *ctxt = _ctxt;
	ESoapMessagePrivate *priv = ctxt->_private;

	if (priv->steal_fd == -1)
		xmlSAX2Characters (ctxt, ch, len);
	else if (!priv->steal_base64) {
		if (write (priv->steal_fd, (const gchar *) ch, len) != len) {
		write_err:

			g_warning ("Failed to write streaming data to file");
		}
	} else {
		guchar *bdata = g_malloc (len);
		gsize blen;

		blen = g_base64_decode_step (
			(const gchar *) ch, len,
			bdata, &priv->steal_b64_state,
			&priv->steal_b64_save);
		if (write (priv->steal_fd, (const gchar *) bdata, blen) != blen) {
			g_free (bdata);
			goto write_err;
		}
		g_free (bdata);
	}
}
