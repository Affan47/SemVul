check_handshake(GIOChannel *channel, GError **err)
{
	GIOGnuTLSChannel *gnutls_channel = (GIOGnuTLSChannel *) channel;
	int result;

	DBG("channel %p", channel);

	if (gnutls_channel->established == TRUE)
		return G_IO_STATUS_NORMAL;

again:
	result = gnutls_handshake(gnutls_channel->session);

	if (result == GNUTLS_E_INTERRUPTED || result == GNUTLS_E_AGAIN) {
		GIOFlags flags = g_io_channel_get_flags(channel);

		if (gnutls_channel->again == TRUE)
			return G_IO_STATUS_AGAIN;

		if (flags & G_IO_FLAG_NONBLOCK)
			return G_IO_STATUS_AGAIN;

		goto again;
	}

	if (result < 0) {
		g_set_error(err, G_IO_CHANNEL_ERROR,
				G_IO_CHANNEL_ERROR_FAILED, "Handshake failed");
		return G_IO_STATUS_ERROR;
	}

	gnutls_channel->established = TRUE;

	DBG("handshake done");

	return G_IO_STATUS_NORMAL;
}
